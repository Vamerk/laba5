import './style.css'
import cytoscape from 'cytoscape'

let counter = 0

document.addEventListener('DOMContentLoaded', () => {
  const instance = cytoscape({
    container: document.getElementById('app'),
    style: [
      {
        selector: 'node',
        style: {
          'background-color': '#666',
          label: 'data(id)',
        },
      },
      {
        selector: 'edge',
        style: {
          width: 3,
          'line-color': '#ccc',
          'curve-style': 'bezier',
          'target-arrow-color': '#ccc',
          'target-arrow-shape': 'triangle',
        },
      },
    ],
  })

  function createNodeEventListener() {
    instance.on('dbltap', (event) => {
        if (event.target == instance) {
          event.cy.add({
            data: { id: String(counter++) },
            position: { x: event.position.x, y: event.position.y },
          })
        }
      })
  }

  createNodeEventListener()

  function joinNodesEventListener() {
    let node = null
    instance.on('dbltap', 'node', (event) => {
      console.log(selectedNode)

      if (node === null) {
        node = event.target
      }
    })
  }
  joinNodesEventListener()
})
