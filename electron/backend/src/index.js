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
    const program = spawn('D:/Workspace/laba5/algoritms/adjacent_matrix/x64/Debug/adjacent_matrix.exe')
    console.log(data)
    program.stdin.write(data)
    program.stdin.end()

    program.stdout.on('data', (data) => {
      console.log(`Recieved from C++: ${data}`)
    })
  })
}

init().catch((error) => {
  console.error(error)
  process.exit(1)
})
