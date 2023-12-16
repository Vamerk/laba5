import './style.css'
import cytoscape from 'cytoscape'

document.addEventListener('DOMContentLoaded', () => {
  const instance = cytoscape({
    container: document.getElementById('app'),
    elements: [
      { data: { id: 'a' } },
      { data: { id: 'b' } },
      { data: { source: 'a', target: 'b' } },
    ],
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
          'target-arrow-color': '#ccc',
          'target-arrow-shape': 'triangle',
        },
      },
    ],
  })

  instance.on("dbltap", (event, params) => {

  })
})
