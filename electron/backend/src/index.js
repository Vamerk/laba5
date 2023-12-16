const path = require('path')
const { app, BrowserWindow } = require('electron');

function createWindow() {
  const window = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js')
    }
  });

  if (process.env.NODE_ENV === "production") {
    window.loadFile(path.join(__dirname, '../../frontend/dist/index.html'));
    return
  }

  window.loadURL("http://localhost:5173")
}

async function init() {
    app.whenReady().then(() => {
        createWindow()

        app.on('activate', () => {
            if (BrowserWindow.getAllWindows().length === 0)
                createWindow()
        })
    })
}

init().catch((error) => {
    console.error(error)
    process.exit(1)
})