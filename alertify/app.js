document.addEventListener("DOMContentLoaded", function () {
    // Initialize Chart.js
    var ctx = document.getElementById("speedometer").getContext("2d");
    var speedometerChart = new Chart(ctx, {
        type: "doughnut",
        data: {
            labels: ["Speed"],
            datasets: [{
                data: [0],
                backgroundColor: ["#36A2EB"],
                borderWidth: 0,
            }],
        },
        options: {
            responsive: true,
            cutout: "80%",
            rotation: Math.PI,
            circumference: Math.PI,
            legend: {
                display: false
            },
            tooltips: {
                enabled: false
            },
            animation: {
                animateRotate: false,
                animateScale: true,
            },
            scale: {
                ticks: {
                    display: false,
                    max: 100,
                    stepSize: 20,
                },
            },
        },
    });

    // Simulate real-time data update
    setInterval(function () {
        // Update the speedometer value (replace this with your real-time data)
        var speedValue = Math.random() * 100;

        // Update the chart data
        speedometerChart.data.datasets[0].data = [speedValue];
        speedometerChart.update();
    }, 1000); // Update every 1000 milliseconds (1 second)
});