const path = require('path')
const { spawn } = require('child_process')
const { app, BrowserWindow, ipcMain } = require('electron')

function createWindow() {
  const window = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js'),
    },
  })

  if (process.env.NODE_ENV === 'production') {
    window.loadFile(path.join(__dirname, '../../frontend/dist/index.html'))
    return
  }

  window.loadURL('http://localhost:5173')
}

async function init() {
  app.whenReady().then(() => {
    createWindow()

    app.on('activate', () => {
      if (BrowserWindow.getAllWindows().length === 0) createWindow()
    })
  })

  ipcMain.on('adjacency-matrix', (event, data) => {
    program = spawn('./cpp/test.exe')

    program.stdout.on('data', (data) => {
      console.log(`Recieved from C++: ${data}`)
    })

    program.stderr.on('data', (data) => {
      console.error(`Error C++: ${data}`)
    })

    program.on('close', (code) => {
      console.log(`C++ exited with ${code}`)
    })
  })
}

init().catch((error) => {
  console.error(error)
  process.exit(1)
})
