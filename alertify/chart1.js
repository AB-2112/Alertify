

async function fetchDataFromCSV() {
     csvFilePath = 'data.csv'; 

    // Fetch data initially
   

// Update the content of the HTML element with the integer from the JSON variable
integerDisplayElement.textContent = jsonData.myInteger;
    // Fetch data periodically (every 5 seconds in this example)
    setInterval(async () => {
     newData = await fetchSpeedData(csvFilePath);
        speedData = newData;
        console.log(`Updated speed data: ${extractDecimalValue(speedData)}`);
    }, 5); // Adjust the interval as needed 
}
//window
window.onload = fetchDataFromCSV;
var ctx = document.getElementById('lineChart').getContext('2d');
var myChart;
var currentTime = 0; 
var accelerationData = []; 

async function fetchDataFromCSV() {
    const csvFilePath = 'data.csv'; 
    const response = await fetch(csvFilePath);

    if (!response.ok) {
        console.error(`Failed to fetch CSV file. Status: ${response.status}`);
       
        return;
    }
   

    const csvData = await response.text();
    const rows = csvData.split('\n');
    function updateChart() {
        if (myChart) {
            myChart.data.labels = Array.from({ length: accelerationData.length }, (_, i) => i.toString());
            myChart.data.datasets[0].data = accelerationData;
            myChart.update();
        }
    }
    
    // Initial chart setup
    myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: Array.from({ length: 10 }, (_, i) => i.toString()), // Initial labels for 10 data points
            datasets: [{
                label: 'Acceleration',
                data: accelerationData,
                backgroundColor: ['rgba(85, 85, 85, 1)'],
                borderColor: 'rgb(41, 155, 99)',
                borderWidth: 1
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: {
                    type: 'linear',
                    position: 'bottom',
                    max: 50, // Set the maximum number of data points to display
                }
            }
        }
    });
    
    function updateChart() {
        if (myChart) {
            // Shift the oldest data point and push the newest one
            accelerationData.shift();
            accelerationData.push(randomAcceleration);
    
            // Shift the oldest label and push the newest one
            myChart.data.labels.shift();
            myChart.data.labels.push((parseInt(myChart.data.labels[myChart.data.labels.length - 1]) + 1).toString());
    
            // Update the chart
            myChart.update();
        }
    }
    
    // Fetch data from CSV in a loop
    setInterval(() => {
        fetchDataFromCSV();
        updateChart();
    }, 2000); // Adjust the interval as needed
    for (let i = 1; i < rows.length; i++) { // Start from index 1 to skip the header
        const row = rows[i].split(',');

        // Assuming you want the speed data (index 0) from the first column of the CSV file
        const speedData = row[0];
       
        // Generate random acceleration data based on speedData (you can replace this with your own logic)
       randomAcceleration = speedData;
       ///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        function getRandomInt(min, max) {
            return Math.floor(Math.random() * (max - min + 1)) + min;
        }
        
        // Replace the hardcoded value with a random integer between 1 and 10 (inclusive)
        const jsonData = {
            myInteger: getRandomInt(1, 5)
        };
        
        // Get the HTML element by its id
        const integerDisplayElement = document.getElementById('integerDisplay');
        
        // Update the content of the HTML element with the integer from the JSON variable
        integerDisplayElement.textContent = jsonData.myInteger;

        // Update current time
        currentTime += 1;

        // Add the generated acceleration data to the array
        accelerationData.push(randomAcceleration);
        // if(i==rows.length-1)
        // i=1;
    }

    // Update the chart after fetching all the data
   // updateChart();
   function refreshPage() {
    setInterval(function () {
        location.reload();
    }, 100000); // 30 seconds in milliseconds
}

// Call the function to start the refresh loop
refreshPage();
}

