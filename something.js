const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const material = new THREE.ShaderMaterial({
    vertexShader: vertexShaderSource,
    fragmentShader: fragmentShaderSource,
});
//this would have to work w/ some glsl code to work.

const geometry = new THREE.SphereGeometry(1, 32, 32);
//constant geometry, cmon man

const mesh = new THREE.Mesh(geometry, material);
scene.add(mesh);
//gotta add mesh, cmon now 
