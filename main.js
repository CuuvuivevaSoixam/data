var pls =[0,0,0,0,0,0,0,0,0,0,0,0]
var temps =[0,0,0,0,0,0,0,0,0,0,0,0]
var hums =[0,0,0,0,0,0,0,0,0,0,0,0]
setInterval(function(){
    let x= Math.floor(Math.random()*30)
    let y = Math.floor(Math.random()*60)
    let z = Math.floor(Math.random()*100)
    
    function fsPolice() {
        document.getElementById("text1").innerHTML = x + " chốt"
        if( x < 10){
            document.getElementById("col1").style.backgroundColor = 'coral'
        }
        else if(  x < 20) {
            document.getElementById("col1").style.backgroundColor = "tomato"
        }
        else {
            document.getElementById("col1").style.backgroundColor = "orangered"
        }
    }
    fsPolice();

    function fsTempurature() {
        document.getElementById("text2").innerHTML =  y + " °C"
        if( y < 20) {
            document.getElementById("col2").style.backgroundColor = "#FFCC66"
        }
        else if( y < 40 ) {
            document.getElementById("col2").style.backgroundColor = "#FFCC33"
        }
        else {
            document.getElementById("col2").style.backgroundColor = "#FF9900"
        }
    }
    fsTempurature();
    
    function fsHumidity() {
        document.getElementById("text3").innerHTML = z + " %"
        if( z < 20) {
            document.getElementById("col3").style.backgroundColor = "#CCFFFF"
        }
        else if( z < 50 ) {
            document.getElementById("col3").style.backgroundColor= "#66FFFF"
        }
        else {
            document.getElementById("col3").style.backgroundColor= "#00FFFF"
        }
    }
    fsHumidity()

    function bieuDo(){
        pls.push(x); pls.shift()
        temps.push(y); temps.shift()
        hums.push(z); hums.shift()
    }

bieuDo()                   
                      
    Highcharts.chart('container', {
        title: {
            text: 'Pikachu , Tempurature and Humidity in HN'
        },                              
        yAxis: {
            min:0,
            max:100
        },
        xAxis: {
          categories: [],
        },                       
        options: {
            scales: {
                y: {
                    beginAtZero: true,     
                }
            },
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        },
                        
         plotOptions: {
            series: {
                label: {
                    connectorAllowed: false
                },
                          
            }
        },
                        
        series: [
            {
                name: 'Police',
                data: pls
            },
            {
                name: 'Tempurature',
                data: temps
            }, 
            {
                name: 'Humidity',
                data: hums
            }
        ],
                        
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 100,
                    minWidth:0
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }  

    });

},2500);


function doimau2(){
  document.getElementById("anh1").src ='light-on.png'
  confirm('xac nhan bat den')
}

 function doimau3(){
    document.getElementById("anh1").src ='light-off.png'
 }
 function swi(){
  if (confirm('banh mi khum')){
    
    document.querySelector('#anh2').src='light-on.png'
    document.querySelector('input').checked=true
  }
  else{
    document.querySelector('input').checked=false
    document.querySelector('#anh2').src='light-off.png'
  }
 }


 