export function createTable(title, data) {
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

  table.caption.addEventListener('click', (event) => {
    table.parentElement.removeChild(table)
  })
}

export function inputPrompt(label) {
  return new Promise((resolve) => {
    const form = document.createElement('form')
    form.classList.add('prompt')
    const input = document.createElement('input')
    input.placeholder = label
    form.appendChild(input)
    const button = document.createElement('button')
    button.type = 'submit'
    button.innerText = 'Подтвердить'
    form.appendChild(button)
    document.body.appendChild(form)

    form.addEventListener('submit', (e) => {
      e.preventDefault()
      const value = input.value
      document.body.removeChild(form)
      resolve(value)
    })
  })
}

export function createColors(length) {
  function randomInteger(max) {
    return Math.floor(Math.random() * (max + 1))
  }

  function randomRgbColor() {
    let r = randomInteger(255)
    let g = randomInteger(255)
    let b = randomInteger(255)
    return [r, g, b]
  }

  function randomHexColor() {
    let [r, g, b] = randomRgbColor()
    let hr = r.toString(16).padStart(2, '0')
    let hg = g.toString(16).padStart(2, '0')
    let hb = b.toString(16).padStart(2, '0')
    return '#' + hr + hg + hb
  }

  const colors = []

  for (let i = 0; i < length; i++) {
    colors.push(randomHexColor())
  }

  return colors
}
