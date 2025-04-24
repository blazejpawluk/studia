const menuIcon = document.getElementById('menuIcon');
const menu = document.getElementById('menu');

menuIcon.addEventListener('click', () => {
	if (menu.style.display === 'none' || menu.style.display === '') {
		menu.style.display = 'block';
	} else {
		menu.style.display = 'none';
	}
});

window.addEventListener('resize', () => {
	if (window.innerWidth >= 750) {
		menu.style.display = 'block';
	} else {
		menu.style.display = 'none';
	}
});

window.addEventListener('load', () => {
	if (window.innerWidth >= 750) {
		menu.style.display = 'block';
	} else {
		menu.style.display = 'none';
	}
});

const homeButton = document.getElementById('homeButton');
const hobbiesButton = document.getElementById('hobbiesButton');
const projectsButton = document.getElementById('projectsButton');

const homeImage = document.getElementById('homeImage');
const hobbiesImage = document.getElementById('hobbyImage');
const projectsImage = document.getElementById('projectImage');

homeButton.addEventListener('mouseenter', () => {
	homeImage.style.display = 'block';
});
homeButton.addEventListener('mouseleave', () => {
	homeImage.style.display = 'none';
});

hobbiesButton.addEventListener('mouseenter', () => {
	hobbiesImage.style.display = 'block';
});
hobbiesButton.addEventListener('mouseleave', () => {
	hobbiesImage.style.display = 'none';
});

projectsButton.addEventListener('mouseenter', () => {
	projectsImage.style.display = 'block';
});
projectsButton.addEventListener('mouseleave', () => {
	projectsImage.style.display = 'none';
});