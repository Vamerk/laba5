import './style.css'
import cytoscape from 'cytoscape'
import { createTable, inputPrompt, createColors } from './utils'

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
          label: 'data(weight)',
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
          weight: 1,
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
          weight: edge.data('weight'),
        },
      })
    })

    instance.remove(instance.elements())
    instance.add(nodes)
    instance.add(edges)

    counter = localCounter
  })

  instance.on('onetap', 'edge', async (event) => {
    try {
      const weight = parseInt(await inputPrompt('Введите вес ребра'))
      if (typeof weight !== 'number' || Number.isNaN(weight)) throw new Error()

      event.target.data('weight', weight)
    } catch (e) {}
  })

  instance.on('dbltap', 'edge', (event) => {
    instance.remove(event.target)
  })

  document.getElementById('adjacency-matrix').addEventListener('click', async () => {
    const jsonData = JSON.stringify({
      data: instance
        .edges()
        .map((edge) => [parseInt(edge.data('source')), parseInt(edge.data('target'))]),
      count: instance.nodes().length,
    })

    const result = JSON.parse(await electron.ipcRenderer.invoke('adjacency-matrix', jsonData))
    createTable('Матрица смежности', result)
  })

  document.getElementById('incidence-matrix').addEventListener('click', async () => {
    const jsonData = JSON.stringify({
      data: instance
        .edges()
        .map((edge) => [parseInt(edge.data('source')), parseInt(edge.data('target'))]),
      count: instance.nodes().length,
    })

    const result = JSON.parse(await electron.ipcRenderer.invoke('incidence-matrix', jsonData))
    createTable('Матрица инциндентности', result)
  })

  document.getElementById('weighted-matrix').addEventListener('click', async () => {
    const edges = []
    const weights = []

    instance.edges().forEach((edge) => {
      edges.push([parseInt(edge.data('source')), parseInt(edge.data('target'))])
      weights.push(parseInt(edge.data('weight')))
    })

    const jsonData = JSON.stringify({
      weights,
      data: edges,
      count: instance.nodes().length,
    })

    console.log(jsonData)

    const result = JSON.parse(await electron.ipcRenderer.invoke('weighted-matrix', jsonData))
    createTable('Весовая матрица', result)
  })

  document.getElementById('color').addEventListener('click', async () => {
    const jsonData = JSON.stringify({
      data: instance
        .edges()
        .map((edge) => [parseInt(edge.data('source')), parseInt(edge.data('target'))]),
      count: instance.nodes().length,
    })

    const result = JSON.parse(await electron.ipcRenderer.invoke('color', jsonData))
    console.log(result)
    const colors = createColors(result.length)

    result.forEach((e) => {
      console.log(colors)
      instance.nodes().getElementById(e[0]).style("background-color", colors[e[1]])
    })
  })
})
