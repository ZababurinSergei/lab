const fs = require('fs');
const { execSync } = require('child_process');

// Чтение аргумента командной строки
const jsonFilePath = process.argv[2];

if (!jsonFilePath) {
    console.error('Ошибка: Укажите путь к JSON файлу');
    console.error('Пример: node solution.js test.json');
    process.exit(1);
}

// Функция для преобразования HEX цвета в уровень активности
function getColorLevel(hexColor) {
    const colorMap = {
        '#ebedf0': 0,
        '#9be9a8': 1,
        '#40c463': 2,
        '#30a14e': 3,
        '#216e39': 4
    };
    return colorMap[hexColor.toLowerCase()] || 0;
}

// Функция для получения количества коммитов для уровня
function getCommitCount(level) {
    const commitMap = {
        0: 0,
        1: 1,
        2: 3,
        3: 6,
        4: 11
    };
    return commitMap[level];
}

// Функция для создания коммита с заданной датой
function createCommit(date, commitNumber, totalInDay) {
    // Форматируем дату в ISO строку с локальным временем
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');

    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    const message = `Activity commit ${timestamp}`;

    try {
        execSync(`git commit --allow-empty -m "${message}"`, {
            env: {
                ...process.env,
                GIT_AUTHOR_DATE: timestamp,
                GIT_COMMITTER_DATE: timestamp
            },
            stdio: 'pipe'
        });
        console.log(`  ✓ Коммит ${commitNumber}/${totalInDay}: ${timestamp}`);
        return true;
    } catch (error) {
        console.error(`  ✗ Ошибка: ${error.message}`);
        return false;
    }
}

// Функция для проверки наличия git репозитория
function ensureGitRepo() {
    try {
        execSync('git rev-parse --git-dir', { stdio: 'pipe' });
        console.log('✓ Git репозиторий найден');
    } catch (error) {
        console.log('✗ Git репозиторий не найден. Создаём...');
        execSync('git init', { stdio: 'pipe' });
        console.log('✓ Git репозиторий создан');
    }
}

// Функция для настройки пользователя git
function setupGitUser() {
    try {
        execSync('git config user.name', { stdio: 'pipe' });
        execSync('git config user.email', { stdio: 'pipe' });
    } catch (error) {
        console.log('⚠️ Настройка git пользователя...');
        execSync('git config user.email "graffiti@example.com"', { stdio: 'pipe' });
        execSync('git config user.name "Git Graffiti"', { stdio: 'pipe' });
        console.log('✓ Git пользователь настроен');
    }
}

// Функция для вычисления начальной даты
function getStartDate(today) {
    // Вычитаем 364 дня
    const startDate = new Date(today);
    startDate.setDate(today.getDate() - 364);

    // Выравниваем к предыдущему воскресенью
    const dayOfWeek = startDate.getDay(); // 0 = воскресенье
    startDate.setDate(startDate.getDate() - dayOfWeek);

    // Устанавливаем время на 12:00:00 (полдень) чтобы избежать проблем с часовыми поясами
    startDate.setHours(12, 0, 0, 0);

    return startDate;
}

// Главная функция для создания heatmap
function generateHeatmap(colors) {
    const today = new Date();
    today.setHours(12, 0, 0, 0); // Устанавливаем полдень для today

    const startDate = getStartDate(today);
    const todayDayOfWeek = today.getDay();

    // Вычисляем количество недель
    const daysDiff = Math.floor((today - startDate) / (1000 * 60 * 60 * 24));
    const numWeeks = Math.ceil((daysDiff + 1) / 7);

    console.log(`\n📅 Параметры:`);
    console.log(`   Сегодня: ${today.toISOString().split('T')[0]}`);
    console.log(`   Начальная дата: ${startDate.toISOString().split('T')[0]}`);
    console.log(`   Недель: ${numWeeks}`);
    console.log(`   День недели сегодня: ${todayDayOfWeek} (0=Вс, 1=Пн, ..., 6=Сб)`);

    // Вычисляем количество колонок для каждой строки
    const colsPerRow = [];
    for (let row = 0; row < 7; row++) {
        if (row <= todayDayOfWeek) {
            colsPerRow[row] = numWeeks;
        } else {
            colsPerRow[row] = numWeeks - 1;
        }
    }

    console.log(`\n📊 Структура heatmap:`);
    const dayNames = ['Воскресенье', 'Понедельник', 'Вторник', 'Среда', 'Четверг', 'Пятница', 'Суббота'];
    for (let row = 0; row < 7; row++) {
        console.log(`   ${dayNames[row]}: ${colsPerRow[row]} колонок`);
    }

    // Проверяем соответствие количества цветов
    const totalCells = colsPerRow.reduce((sum, cols) => sum + cols, 0);
    console.log(`\n📦 Данные:`);
    console.log(`   Всего ячеек в heatmap: ${totalCells}`);
    console.log(`   Получено цветов: ${colors.length}`);

    if (colors.length !== totalCells) {
        console.warn(`   ⚠️ ВНИМАНИЕ: Количество цветов (${colors.length}) не совпадает с количеством ячеек (${totalCells})`);
        console.warn(`   Будет использовано только ${Math.min(colors.length, totalCells)} ячеек`);
    }

    console.log(`\n🚀 Начинаем создание коммитов...\n`);

    let totalCommits = 0;
    let processedCells = 0;

    // Обходим ячейки в row-major порядке
    for (let row = 0; row < 7; row++) {
        const numCols = colsPerRow[row];

        for (let col = 0; col < numCols; col++) {
            if (processedCells >= colors.length) {
                console.log(`\n⚠️ Достигнут конец массива цветов (обработано ${processedCells} ячеек)`);
                break;
            }

            const color = colors[processedCells];
            const level = getColorLevel(color);
            const commitsNeeded = getCommitCount(level);

            // Вычисляем дату для этой ячейки
            const cellDate = new Date(startDate);
            cellDate.setDate(startDate.getDate() + (col * 7) + row);

            // Форматируем дату для отображения
            const dateStr = cellDate.toISOString().split('T')[0];
            const dayName = dayNames[row];
            const weekNum = col + 1;

            // Пропускаем будущие даты
            if (cellDate > today) {
                console.log(`⏭️  [${row},${col}] ${dayName}, неделя ${weekNum} (${dateStr}) - будущая дата, пропущено`);
                processedCells++;
                continue;
            }

            if (commitsNeeded > 0) {
                console.log(`📝 [${row},${col}] ${dayName}, неделя ${weekNum} (${dateStr}):`);
                console.log(`   Цвет: ${color} → Уровень: ${level} → Нужно коммитов: ${commitsNeeded}`);

                // Создаем коммиты с разными временами в течение дня
                for (let i = 0; i < commitsNeeded; i++) {
                    const commitDate = new Date(cellDate);
                    // Распределяем коммиты в течение дня (9:00 - 17:00)
                    const hour = 9 + Math.floor(i / 6);
                    const minute = (i % 6) * 10;
                    commitDate.setHours(hour, minute, i, 0);

                    createCommit(commitDate, i + 1, commitsNeeded);
                    totalCommits++;
                }
                console.log(`   ✅ Создано ${commitsNeeded} коммитов\n`);
            } else {
                console.log(`⏭️  [${row},${col}] ${dayName}, неделя ${weekNum} (${dateStr}): ${color} → уровень 0 → нет коммитов\n`);
            }

            processedCells++;
        }

        if (processedCells >= colors.length) break;
    }

    console.log(`\n✨ РЕЗУЛЬТАТ:`);
    console.log(`   Обработано ячеек: ${processedCells}`);
    console.log(`   Создано коммитов: ${totalCommits}`);

    if (processedCells < totalCells) {
        console.log(`   ⚠️ Внимание: Не все ячейки были обработаны из-за нехватки данных`);
    }
}

// Функция для проверки дат коммитов
function verifyCommits() {
    console.log(`\n🔍 Проверка созданных коммитов:`);
    try {
        const log = execSync('git log --format="%ad %s" --date=iso-strict | head -10', { encoding: 'utf8' });
        console.log(log);
    } catch (error) {
        console.log('Нет коммитов для отображения');
    }
}

// Основная функция
function main() {
    try {
        console.log('🎨 Git Graffiti - Генератор heatmap\n');

        // Читаем JSON файл
        console.log(`📂 Чтение файла: ${jsonFilePath}`);
        const colorsData = fs.readFileSync(jsonFilePath, 'utf8');
        const colors = JSON.parse(colorsData);

        console.log(`🎨 Загружено цветов: ${colors.length}`);
        console.log(`📋 Первые 5 цветов: ${colors.slice(0, 5).join(', ')}...`);

        // Проверяем git окружение
        ensureGitRepo();
        setupGitUser();

        // Генерируем heatmap
        generateHeatmap(colors);

        // Показываем статистику
        verifyCommits();

        console.log(`\n💡 Следующие шаги:`);
        console.log(`   1. Проверьте коммиты: git log --oneline`);
        console.log(`   2. Посмотрите статистику: git shortlog -sn`);
        console.log(`   3. Для публикации на GitHub: git remote add origin <url>`);
        console.log(`   4. Отправьте на GitHub: git push -u origin main`);

    } catch (error) {
        console.error(`\n❌ Ошибка: ${error.message}`);
        if (error.code === 'ENOENT') {
            console.error(`   Файл "${jsonFilePath}" не найден`);
        }
        process.exit(1);
    }
}

// Запуск
main();