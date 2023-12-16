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
        selector: 'node.selected',
        style: {
          'border-width': 2,
          'border-color': 'red',
          'border-style': 'solid',
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

  let node = null

  instance.on('tap', (event) => {
    if (event.target == instance) {
      event.cy.add({
        data: { id: String(counter++) },
        position: { x: event.position.x, y: event.position.y },
      })
    }
  })

  instance.on('tap', 'node', (event) => {
    if (node === null) {
      node = event.target
      node.addClass('selected')
      return
    }

    try {
      instance.add({
        data: {
          id: `${node.id()}-${event.target.id()}`,
          source: node.id(),
          target: event.target.id(),
        },
      })
    } catch (e) {}

    node.removeClass('selected')
    node = null
  })

  instance.on('dbltap', 'node', (event) => {
    instance.filter((element, index, collection) => {
      if (element.group() == "edges") {
      }
    })
  })

  instance.on('tap', 'edge', (event) => {
    instance.remove(event.target)
  })
})
