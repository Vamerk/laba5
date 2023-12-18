const path = require('path')
const { spawn } = require('child_process')
const { app, BrowserWindow, ipcMain } = require('electron')

let window

function createWindow() {
  window = new BrowserWindow({
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

  ipcMain.handle(
    'adjacency-matrix',
    async (event, data) =>
      new Promise((resolve, reject) => {
        const program = spawn(
          'D:/Workspace/laba5/algoritms/adjacent_matrix/x64/Debug/adjacent_matrix.exe',
        )
        program.stdin.write(data)
        program.stdin.end()

        program.stdout.on('data', (data) => {
          resolve(String(data))
        })

        program.stderr.on('data', (data) => {
          reject(data)
        })
      }),
  )

  ipcMain.handle(
    'incidence-matrix',
    async (event, data) =>
      new Promise((resolve, reject) => {
        const program = spawn(
          'D:/Workspace/laba5/algoritms/incidence_matrix/x64/Debug/IncidenceMatrix.exe',
        )
        program.stdin.write(data)
        program.stdin.end()

        program.stdout.on('data', (data) => {
          resolve(String(data))
        })

        program.stderr.on('data', (data) => {
          reject(data)
        })
      }),
  )

  ipcMain.handle(
    'weighted-matrix',
    async (event, data) =>
      new Promise((resolve, reject) => {
        const program = spawn(
          'D:/Workspace/laba5/algoritms/weighted_matrix/x64/Debug/Weighted Matrix.exe',
        )
        program.stdin.write(data)
        program.stdin.end()

        program.stdout.on('data', (data) => {
          resolve(String(data))
        })

        program.stderr.on('data', (data) => {
          reject(data)
        })
      }),
  )

  ipcMain.handle(
    'color',
    async (event, data) =>
      new Promise((resolve, reject) => {
        const program = spawn(
          'D:/Workspace/laba5/algoritms/coloring/x64/Debug/coloring.exe',
        )
        program.stdin.write(data)
        program.stdin.end()

        program.stdout.on('data', (data) => {
          resolve(String(data))
        })

        program.stderr.on('data', (data) => {
          reject(data)
        })
      }),
  )
}

init().catch((error) => {
  console.error(error)
  process.exit(1)
})
