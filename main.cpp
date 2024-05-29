#include <GL/glut.h>
#include <cmath>
#include <map>

// Variables de la cámara
float camaraX = 0.0f;
float camaraY = 1.75f; // Altura de una persona promedio
float camaraZ = 5.0f;
float camaraAngulo = 0.0f;
float camaraVelocidad = 0.02f; // Velocidad de desplazamiento
float rotacionVelocidad = 0.01f; // Velocidad de rotación

using namespace std;

// Mapa para el estado de las teclas
map<unsigned char, bool> keyState;

// Función de inicialización
void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Color de fondo
    glEnable(GL_DEPTH_TEST); // Habilita el test de profundidad
    glMatrixMode(GL_PROJECTION); // Selecciona la matriz de proyección
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0); // Configura la perspectiva
}

// Función de redimensionamiento de la ventana
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 1000.0);
}

// Función para dibujar el piso
void dibujarPiso() {
    glColor3f(0.3f, 0.3f, 0.3f); // Color gris oscuro
    glBegin(GL_QUADS);
        glVertex3f(-50.0f, 0.0f, -50.0f);
        glVertex3f( 50.0f, 0.0f, -50.0f);
        glVertex3f( 50.0f, 0.0f,  50.0f);
        glVertex3f(-50.0f, 0.0f,  50.0f);
    glEnd();
}

// Función de renderizado
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Configura la cámara en la posición y ángulo actual
    gluLookAt(camaraX, camaraY, camaraZ,
              camaraX + sin(camaraAngulo), camaraY, camaraZ - cos(camaraAngulo),
              0.0f, 1.0f, 0.0f);

    // Dibujar el piso
    dibujarPiso();

    // Dibujar el edificio (una caja simple como ejemplo)
    glColor3f(0.549f, 0.624f, 0.698f); // Color azul grisáceo
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f( 1.0f, 0.0f, -1.0f);
        glVertex3f( 1.0f, 2.0f, -1.0f);
        glVertex3f(-1.0f, 2.0f, -1.0f);
        // Atrás
        glVertex3f(-1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f, 2.0f, 1.0f);
        glVertex3f(-1.0f, 2.0f, 1.0f);
        // Izquierda
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f,  1.0f);
        glVertex3f(-1.0f, 2.0f,  1.0f);
        glVertex3f(-1.0f, 2.0f, -1.0f);
        // Derecha
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f,  1.0f);
        glVertex3f(1.0f, 2.0f,  1.0f);
        glVertex3f(1.0f, 2.0f, -1.0f);
        // Arriba
        glVertex3f(-1.0f, 2.0f, -1.0f);
        glVertex3f( 1.0f, 2.0f, -1.0f);
        glVertex3f( 1.0f, 2.0f,  1.0f);
        glVertex3f(-1.0f, 2.0f,  1.0f);
        // Abajo
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f( 1.0f, 0.0f, -1.0f);
        glVertex3f( 1.0f, 0.0f,  1.0f);
        glVertex3f(-1.0f, 0.0f,  1.0f);
    glEnd();

    glutSwapBuffers();
}

// Función para actualizar la posición de la cámara
void actualizarCamara() {
    if (keyState['w']) {
        camaraX += sin(camaraAngulo) * camaraVelocidad;
        camaraZ -= cos(camaraAngulo) * camaraVelocidad;
    }
    if (keyState['s']) {
        camaraX -= sin(camaraAngulo) * camaraVelocidad;
        camaraZ += cos(camaraAngulo) * camaraVelocidad;
    }
    if (keyState['a']) {
        camaraX -= cos(camaraAngulo) * camaraVelocidad;
        camaraZ -= sin(camaraAngulo) * camaraVelocidad;
    }
    if (keyState['d']) {
        camaraX += cos(camaraAngulo) * camaraVelocidad;
        camaraZ += sin(camaraAngulo) * camaraVelocidad;
    }
    if (keyState['q']) { // Rotar a la izquierda
        camaraAngulo -= rotacionVelocidad;
    }
    if (keyState['e']) { // Rotar a la derecha
        camaraAngulo += rotacionVelocidad;
    }
    glutPostRedisplay();
}

// Función para manejar las teclas presionadas
void detectarTeclaPresionada(unsigned char key, int x, int y) {
    keyState[key] = true;
}

// Función para manejar las teclas liberadas
void detectarTeclaNoPresionada(unsigned char key, int x, int y) {
    keyState[key] = false;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Recorrido por un edificio en OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(actualizarCamara); // Llamada a la función de actualización en cada frame
    glutKeyboardFunc(detectarTeclaPresionada);//
    glutKeyboardUpFunc(detectarTeclaNoPresionada);

    glutMainLoop();
    return 0;
}
