- Для сборки необходима библиотека WxWidgets и  DPP
- Программа для удаления сообщений с дискорд сервера .

- При входе в программу введите токен вашего бота который вы добавили на сервер .

- После открытия основного окна программы,введите id канала при вхоже в программу и бот сразу покажет весь список серверов на канале. 

- Для того чтоб бот мог удалять сообщения нужно предоставить ему права для удаления в настройках Discord.

- После можно выбрать промежуток времени и имя сервера в котором нужно удалить Сообщения

Команды для компиляции с помощью Cmake .
-
- 1: Войдите в папку build  и введите (cmake ..) , после окончания процесса введите cmake --build . и после окончания процесса  запустите файл main .

Вот команды Для сборки и запуска через flatpak

- 1: Откройте в консоли папку Flatpak

- 2: Установите зависимости под вашу систему
- sudo apt install flatpak flatpak-builder
- flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
- flatpak install org.freedesktop.Platform//23.08
- flatpak install org.freedesktop.Sdk//23.08

3: команда для сборки и установки пакета . Скачает и установит все зависимости после саму программу . 
flatpak-builder --user --install build-dir com.remove_discord.MyApp.yml --force-clean

4: Запуск
flatpak run com.remove_discord.MyApp

5: Удаление
flatpak uninstall  com.remove_discord.MyApp

Работает на Windows и Linux, под Mac не проверял.
