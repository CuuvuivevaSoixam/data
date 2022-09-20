 function doimau1() {
    const x = document.getElementById("box1").value
    if (x<20) {
        col1.style.background='blue'
    }else if(x<30){
        col1.style.background='back'
    }else{
        col1.style.background='red'
        alert('de so be thoi broooo!!!!')
    }
}
 function doimau2(){
     document.getElementById("nut1").style.background = 'red'
    
 }
 function doimau3(){
     document.getElementById("nut1").style.background ='blue'
 }
 function resetMyForm(){
    document.getElementById("nut2").reset()
 }