const { spawn } = require('child_process')

const cppProcess = spawn('./cpp/test.exe')

// Отправляем данные из Node.js в C++
const inputData = 'Hello from Node.js!';
cppProcess.stdin.write(inputData);
cppProcess.stdin.end(); 

// Обрабатываем вывод C++ программы
cppProcess.stdout.on('data', (data) => {
  console.log(`Получено из C++: ${data}`);
});

// Обрабатываем ошибки, если они возникнут
cppProcess.stderr.on('data', (data) => {
  console.error(`Ошибка из C++: ${data}`);
});

// Обрабатываем завершение C++ программы
cppProcess.on('close', (code) => {
  console.log(`C++ программа завершилась с кодом ${code}`);
});