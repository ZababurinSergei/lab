function parsePattern(pattern) {
    const segments = [];
    let i = 0;

    while (i < pattern.length) {
        if (pattern[i] === '[') {
            const end = pattern.indexOf(']', i);
            if (end === -1) throw new Error('Invalid pattern');

            let paramContent = pattern.substring(i + 1, end);
            let name = paramContent;
            let optional = false;
            let caseInsensitive = false;

            if (paramContent.includes('?')) {
                optional = true;
                name = name.replace('?', '');
            }
            if (paramContent.includes('~')) {
                caseInsensitive = true;
                name = name.replace('~', '');
            }

            segments.push({
                type: 'param',
                name: name,
                optional: optional,
                caseInsensitive: caseInsensitive
            });

            i = end + 1;
        } else {
            let j = i;
            while (j < pattern.length && pattern[j] !== '[') {
                j++;
            }
            segments.push({
                type: 'text',
                value: pattern.substring(i, j)
            });
            i = j;
        }
    }

    return segments;
}

function matchPattern(path, patternSegments) {
    const pathSegments = path.split('/').filter(s => s.length > 0);

    function matchRecursive(patternIdx, pathIdx, collectedParams) {
        if (patternIdx === patternSegments.length) {
            return pathIdx === pathSegments.length ? collectedParams : null;
        }

        if (pathIdx === pathSegments.length) {
            for (let i = patternIdx; i < patternSegments.length; i++) {
                if (patternSegments[i].type === 'param' && !patternSegments[i].optional) {
                    return null;
                }
                if (patternSegments[i].type === 'text') {
                    return null;
                }
            }
            return collectedParams;
        }

        const currentPattern = patternSegments[patternIdx];

        if (currentPattern.type === 'text') {
            if (pathSegments[pathIdx] !== currentPattern.value) {
                return null;
            }
            return matchRecursive(patternIdx + 1, pathIdx + 1, collectedParams);
        }
        else if (currentPattern.type === 'param') {
            let paramValue = pathSegments[pathIdx];

            if (/^[a-zA-Z0-9_-]+$/.test(paramValue)) {
                if (currentPattern.caseInsensitive) {
                    paramValue = paramValue.toLowerCase();
                }

                const newParams = { ...collectedParams, [currentPattern.name]: paramValue };
                const result = matchRecursive(patternIdx + 1, pathIdx + 1, newParams);
                if (result !== null) {
                    return result;
                }
            }

            if (currentPattern.optional) {
                return matchRecursive(patternIdx + 1, pathIdx, collectedParams);
            }

            return null;
        }

        return null;
    }

    return matchRecursive(0, 0, {});
}

function substituteParams(str, params) {
    return str.replace(/\{([a-zA-Z0-9_-]+)\}/g, (match, paramName) => {
        return params[paramName] !== undefined ? params[paramName] : match;
    });
}

async function executeProcessors(processors, globalProcessors, params) {
    for (const processorName of processors) {
        const processor = globalProcessors[processorName];
        if (!processor || typeof processor !== 'function') {
            throw new Error(`Processor "${processorName}" not found`);
        }

        const result = await processor(params);
        if (typeof result === 'string') {
            return result;
        }
    }
    return null;
}

module.exports = async function interpretNavConfig(config, inputPath) {
    const { pathRules, processors = {}, errorPath } = config;
    let currentPath = inputPath;
    const visitedPaths = new Set();
    let maxIterations = 100;

    while (maxIterations-- > 0) {
        if (visitedPaths.has(currentPath)) {
            return errorPath;
        }
        visitedPaths.add(currentPath);

        let matchedRule = null;
        let matchedParams = null;

        for (const rule of pathRules) {
            try {
                const patternSegments = parsePattern(rule.pattern);
                const params = matchPattern(currentPath, patternSegments);

                if (params !== null) {
                    matchedRule = rule;
                    matchedParams = params;
                    break;
                }
            } catch (error) {
                continue;
            }
        }

        if (!matchedRule) {
            return errorPath;
        }

        if (matchedRule.redirect) {
            currentPath = substituteParams(matchedRule.redirect, matchedParams);
            continue;
        }

        if (matchedRule.processors && matchedRule.processors.length > 0) {
            try {
                const newPath = await executeProcessors(matchedRule.processors, processors, matchedParams);
                if (newPath !== null && typeof newPath === 'string') {
                    currentPath = newPath;
                    continue;
                }
            } catch (error) {
                return errorPath;
            }
        }

        if (matchedRule.destination) {
            return substituteParams(matchedRule.destination, matchedParams);
        }

        return errorPath;
    }

    return errorPath;
};