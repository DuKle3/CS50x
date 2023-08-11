document.addEventListener('DOMContentLoaded', function(){
    var night = document.querySelector('.Night');
    var check = 0;
    night.addEventListener('click', function(){
        if (check == 0) {
            document.querySelector('.NightBody').style.backgroundColor = '#333333';
            document.querySelector('.NightBody').style.color = '#ffffff';
            check++;
        }
        else {
            document.querySelector('.NightBody').style.backgroundColor = '#ffffff';
            document.querySelector('.NightBody').style.color = '#0d0d0d';
            check--;
        }
    });
});

function changeColorEvent(event)
{
    var triggerObject = event.srcElement;
    document.querySelector('.colorDiv').style.backgroundColor = triggerObject.innerHTML.toLowerCase()
};


function changeFontEvent(event)
{
    var triggerObject1 = event.srcElement;
    document.querySelector('.colorDiv').style.fontFamily = triggerObject1.innerHTML.toLowerCase()
};