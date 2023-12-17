const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('electron', {
  adjacencyMatrix: (message) => ipcRenderer.send('adjacency-matrix', message),
})