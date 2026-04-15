// test-correct.js
const interpretNavConfig = require('./solution.js');

async function runTests() {
    console.log('=== Запуск тестов из задачи ===\n');

    // Пример 1. Простое сопоставление
    console.log('Тест 1: Простое сопоставление');
    const config1 = {
        pathRules: [
            { pattern: "users[id]", destination: "/pages/user.html" }
        ],
        errorPath: "/pages/error.html"
    };
    const result1 = await interpretNavConfig(config1, "users/abc-01");
    console.log(`Результат: ${result1}`);
    console.log(`Ожидается: /pages/user.html`);
    console.log(result1 === "/pages/user.html" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Пример 2. Опциональный параметр (?)
    console.log('Тест 2: Опциональный параметр');
    const config2 = {
        pathRules: [
            { pattern: "archive[year][month?]", destination: "/pages/archive.html" }
        ],
        errorPath: "/pages/error.html"
    };
    const result2 = await interpretNavConfig(config2, "archive/2024");
    console.log(`Результат: ${result2}`);
    console.log(`Ожидается: /pages/archive.html`);
    console.log(result2 === "/pages/archive.html" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Пример 3. Лишний сегмент
    console.log('Тест 3: Лишний сегмент');
    const config3 = {
        pathRules: [
            { pattern: "a[b?]", destination: "/ok" }
        ],
        errorPath: "/err"
    };
    const result3 = await interpretNavConfig(config3, "a/b/c");
    console.log(`Результат: ${result3}`);
    console.log(`Ожидается: /err`);
    console.log(result3 === "/err" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Дополнительный тест: Редирект (из описания алгоритма)
    console.log('Тест 4: Редирект');
    const config4 = {
        pathRules: [
            { pattern: "old[id]", redirect: "new/{id}" },
            { pattern: "new[id]", destination: "/pages/new_{id}.html" }
        ],
        errorPath: "/err"
    };
    const result4 = await interpretNavConfig(config4, "old/123");
    console.log(`Результат: ${result4}`);
    console.log(`Ожидается: /pages/new_123.html`);
    console.log(result4 === "/pages/new_123.html" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Дополнительный тест: Регистронезависимый параметр (~)
    console.log('Тест 5: Регистронезависимый параметр');
    const config5 = {
        pathRules: [
            { pattern: "search[query~]", destination: "/search/{query}" }
        ],
        errorPath: "/err"
    };
    const result5 = await interpretNavConfig(config5, "search/HELLO");
    console.log(`Результат: ${result5}`);
    console.log(`Ожидается: /search/hello`);
    console.log(result5 === "/search/hello" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Дополнительный тест: Опциональный параметр в середине
    console.log('Тест 6: Опциональный параметр в середине');
    const config6 = {
        pathRules: [
            { pattern: "page[lang?][id]", destination: "/content/{id}" }
        ],
        errorPath: "/err"
    };
    const result6a = await interpretNavConfig(config6, "page/ru/123");
    console.log(`Путь "page/ru/123" -> ${result6a}`);
    const result6b = await interpretNavConfig(config6, "page/123");
    console.log(`Путь "page/123" -> ${result6b}`);
    console.log(`Ожидается: /content/123 для обоих случаев`);
    console.log((result6a === "/content/123" && result6b === "/content/123") ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Дополнительный тест: Несколько параметров в сегменте
    console.log('Тест 7: Несколько параметров в сегменте');
    const config7 = {
        pathRules: [
            { pattern: "product[id][color?]", destination: "/products/{id}" }
        ],
        errorPath: "/err"
    };
    const result7 = await interpretNavConfig(config7, "product/abc123/red");
    console.log(`Результат: ${result7}`);
    console.log(`Ожидается: /products/abc123`);
    console.log(result7 === "/products/abc123" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
    console.log('');

    // Тест на валидацию символов
    console.log('Тест 8: Валидация символов (недопустимые символы)');
    const config8 = {
        pathRules: [
            { pattern: "users[id]", destination: "/pages/user.html" }
        ],
        errorPath: "/err"
    };
    const result8 = await interpretNavConfig(config8, "users/abc@123");
    console.log(`Путь "users/abc@123" -> ${result8}`);
    console.log(`Ожидается: /err`);
    console.log(result8 === "/err" ? '✅ ПРОЙДЕН' : '❌ НЕ ПРОЙДЕН');
}

// Запускаем тесты
runTests().catch(console.error);