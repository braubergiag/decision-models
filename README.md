# Программная система DecisionModels
*DecisionModels* - программная система для работы с многокритериальными задачами принятия решений.
Проект выполняется в рамках научно-исследовательской работы. <br>
**Научный руководитель**:
д. ф.-м. н., профессор Н. К. Кривулин 
# Инструкция по сборке (Linux)
## Debian/Ubuntu

Установка зависимостей
```bash
sudo apt-get update
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt install cmake 
sudo apt install qt6-base-dev 
sudo apt install libeigen3-dev
```
Сборка и запуск
```bash
git clone https://github.com/braubergiag/decision-models.git
cd decision-models
mkdir build
cd build
cmake ..
cmake --build .
./DecisionModels
```