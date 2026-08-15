Igal Shturman Poplawsky 18139

Descripción del Programa

Este proyecto es una aplicación de consola desarrollada en C++ que demuestra la implementación y funcionamiento de algoritmos de ordenamiento aplicados a estructuras de datos personalizadas (Listas Ligadas). El programa genera un conjunto de datos aleatorios, empleando una barra de progreso visual para indicar la carga, y posteriormente evalúa y compara la ejecución de los métodos de ordenamiento Selection Sort e Insertion Sort sobre copias idénticas de los datos. Además, integra una clase utilitaria (ConsoleUI) encargada de mejorar la experiencia de usuario en consola mediante el uso de texto a color, separadores, limpieza de pantalla y formato tabular.
Decisión de Diseño: PrintTitle con ancho insuficiente

En el método ConsoleUI::PrintTitle(std::string texto, int ancho), se implementó una validación para evitar que un parámetro de ancho (ancho) menor a la longitud del texto rompa el formato visual de la consola.

Decisión:
Si el usuario especifica un ancho que es menor a la longitud del texto más un margen mínimo de 4 caracteres, el método sobreescribe este valor y autoajusta el ancho a texto.length() + 4.

Justificación:
Esta medida defensiva garantiza que el texto del título nunca se corte, se desborde o quede pegado a los bordes de la caja de caracteres (=). Al forzar un margen de seguridad de al menos 2 espacios por lado (izquierdo y derecho), se preserva la legibilidad y la estética de la interfaz de usuario bajo cualquier circunstancia, evitando comportamientos visuales inesperados si se introduce un dato erróneo al llamar a la función.