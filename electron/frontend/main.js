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
    if (event.target === instance) {
      if (node === null) {
        event.cy.add({
          data: { id: String(counter++) },
          position: { x: event.position.x, y: event.position.y },
        })
        return
      }

      node.removeClass('selected')
      node = null
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
    const edge = instance.filter((element) => {
      return (
        element.group() === 'edges' &&
        (element.source() === event.target || element.target() == event.target)
      )
    })

    instance.remove(edge)
    instance.remove(event.target)

    let localCounter = 0
    const nodes = []
    const edges = []
    const mappings = {}

    instance
      .nodes()
      .sort((e1, e2) => parseInt(e1.id() - e2.id()))
      .forEach((element) => {
        mappings[element.id()] = String(localCounter)

        nodes.push({
          data: { id: String(localCounter) },
          position: { x: element.position().x, y: element.position().y },
        })
        localCounter++
      })

    instance.edges().map((edge) => {
      const source = mappings[edge.source().id()]
      const target = mappings[edge.target().id()]

      edges.push({
        data: {
          id: `${source}-${target}`,
          source,
          target,
        },
      })
    })

    instance.remove(instance.elements())
    instance.add(nodes)
    instance.add(edges)

    counter = localCounter
  })

  instance.on('tap', 'edge', (event) => {
    instance.remove(event.target)
  })

  const adjacencyMatrixButton = document.getElementById('adjacency-matrix')
  adjacencyMatrixButton.addEventListener('click', async () => {
    const jsonData = JSON.stringify({
      data: instance
        .edges()
        .map((edge) => [parseInt(edge.data('source')), parseInt(edge.data('target'))]),
      count: instance.nodes().length,
    })

    const result = JSON.parse(await electron.ipcRenderer.invoke('adjacency-matrix', jsonData))
    showTable('Матрица смежности', result)
  })
})

function showTable(title, data) {
  const table = document.createElement('table')
  const tableCaption = table.createCaption()
  const tableHead = table.createTHead()
  const tableBody = table.createTBody()

  tableCaption.appendChild(document.createTextNode(title))

  const headerRow = document.createElement('tr')
  headerRow.appendChild(document.createElement('td'))
  for (let i = 0; i < data.length; i++) {
    const th = document.createElement('th')
    th.appendChild(document.createTextNode(String(i)))
    headerRow.appendChild(th)
  }
  tableHead.appendChild(headerRow)

  for (let i = 0; i < data.length; i++) {
    const tr = document.createElement('tr')
    const th = document.createElement('th')
    th.appendChild(document.createTextNode(String(i)))
    tr.appendChild(th)

    for (let j = 0; j < data[i].length; j++) {
      const td = document.createElement('td')
      td.appendChild(document.createTextNode(String(data[i][j])))
      tr.appendChild(td)
    }

    tableBody.appendChild(tr)
  }

  document.getElementById('output').appendChild(table)
}
