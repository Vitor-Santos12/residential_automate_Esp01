function controlGPIO(action) {
    const gpio = document.getElementById("gpio-select").value;
    
    // Enviar solicitação para o servidor
    fetch(`/gpio/${gpio}/${action}`)
        .then(response => response.json())
        .then(data => {
            document.getElementById("gpio-status").innerText = data.status ? "ON" : "OFF";
        })
        .catch(error => console.error('Error:', error));
}

function scheduleIrrigation() {
    const startTime = document.getElementById("start-time").value;
    const endTime = document.getElementById("end-time").value;
    const repeat = document.getElementById("repeat").value;

    const schedule = {
        startTime,
        endTime,
        repeat
    };

    // Enviar solicitação para agendar a irrigação
    fetch('/schedule', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(schedule),
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("next-schedule").innerText = data.nextSchedule || "None";
    })
    .catch(error => console.error('Error:', error));
}

// Obter status inicial
function getStatus() {
    fetch('/status')
        .then(response => response.json())
        .then(data => {
            document.getElementById("gpio-status").innerText = data.gpioStatus ? "ON" : "OFF";
            document.getElementById("next-schedule").innerText = data.nextSchedule || "None";
        })
        .catch(error => console.error('Error:', error));
}

// Atualizar status ao carregar a página
window.onload = getStatus;
