const cards = document.querySelectorAll('.card');
const answerKey = ["b","u","n","y","a"]
const startButton = document.getElementById("button") 
const scoreTag = document.getElementById("score")
let cardContainer = document.getElementById("card-container");

let imgList = Array.from(cardContainer.getElementsByTagName("img"));

let count=0
let score

startButton.addEventListener('click', startGame);


function getImages(){
    cardContainer = document.getElementById("card-container");
    imgList = Array.from(cardContainer.getElementsByTagName("img"));
}

function updateImages(){
    cardContainer.innerHTML = "";
    imgList.forEach(function (img) {
        cardContainer.appendChild(img);
    });
}

function shuffleImages(){
    getImages()
    imgList= shuffleArray(imgList)
    updateImages()
}

function shuffleArray(array) {
    const shuffledArray = array.slice();

    for (let i = shuffledArray.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [shuffledArray[i], shuffledArray[j]] = [shuffledArray[j], shuffledArray[i]];
    }
    return shuffledArray;
}

function black(){
    getImages()
    imgList.forEach(function (img) {
        img.src = "empty.jpeg";
    });
    updateImages()
}

function show() {
    getImages()
    imgList.forEach(function (img) {
        img.src = img.id+".svg";
    });
    updateImages()
}
function removeListeners() {
    getImages()
    imgList.forEach((img)=>img.removeEventListener("click", imgClick))
    
}

function imgClick() {
    black()
    if (answerKey[count]==this.id) {
        score+=20
        scoreTag.innerHTML=score
        this.src = this.id+".svg"
        setTimeout(()=>{this.src = "empty.jpeg"},2000)
        if (score==100) {
            setTimeout(()=>{alert("CONGRATULATIONS, Your Score is 100!!!")},200)
            removeListeners()
        }
    } else {
        alert("Game Over, Your Score is "+score)
        removeListeners()
    }
    count++
}

function startGame(){
    show()
    count=0
    score=0
    shuffleImages()
    setTimeout(black ,2000)
    updateImages()
    imgList.forEach((img)=>img.addEventListener("click",imgClick))

}
