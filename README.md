# ⚛️ ¿Qué es esto?
Este proyecto consiste en utilizar la librería [SDL](https://wiki.libsdl.org/SDL3/FrontPage) para recrear el movimiento de un pendulo (no necesáriamente simple). Se utilizarán métodos numéricos para simular la posición del péndulo en cada instante de tiempo.

# ⚙️ Tech Stack
Este programa está completamente desarrollado en C, utilizando SDL para los gráficos.

# 🚧 Compatibilidad
Actualmente este programa solo está compilado para Linux, pero teniendo el código base, se puede simplemente compilar a un ejecutable de cualquier otro sistema operativo.

# 📝 Objetivos
- [x] Péndulo funcional.
- [ ] Gráfica del ángulo $\theta (t)$ en función del tiempo.
- [ ] Implementación de un archivo `azPendulum.config` para modificar el comportamiento y/o condiciones iniciales del péndulo desde un archivo externo.
- [ ] Dibujado de los círculos mediante la GPU.