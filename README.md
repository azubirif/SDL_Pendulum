# ⚛️ ¿Qué es esto?
Este proyecto consiste en utilizar la librería [SDL](https://wiki.libsdl.org/SDL3/FrontPage) para recrear el movimiento de un pendulo (no necesáriamente simple). Se utilizarán métodos numéricos para simular la posición del péndulo en cada instante de tiempo.

# ⚙️ Tech Stack
Este programa está completamente desarrollado en C, utilizando SDL para los gráficos.

# 🔢 Apartado teórico
El programa utiliza el método de Euler para calcular los valores que toma la función $\theta (t)$ numéricamente. El valor de paso $h$ se puede personalizar para una mayor precisión. En el código, es la constante `STEP`. 

# 🚧 Compatibilidad
Actualmente este programa solo está compilado para Linux, pero teniendo el código base, se puede simplemente compilar a un ejecutable de cualquier otro sistema operativo.

# 📝 Objetivos
- [x] Péndulo funcional.
- [ ] Gráfica del ángulo $\theta (t)$ en función del tiempo.
- [ ] Implementación de un archivo `azPendulum.config` para modificar el comportamiento y/o condiciones iniciales del péndulo desde un archivo externo.
- [ ] Dibujado de los círculos mediante la GPU.
- [ ] Optimización de los cálculos numéricos mediante la GPU.
- [ ] Vídeo explicativo en YouTube.