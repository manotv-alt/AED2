Para executar esse programa é necessário a instalação da biblioteca libpng.

- Se quiser mudar o texto a ser escondido na imagem, basta trocá-lo entre as aspas no arquivo "input.h".
- Se quiser mudar a imagem na qual o texto vai ser escondido, basta adiciona-lá na pasta "img" e mudar o endereço, na main "esteganografia.c", da variávle "fileName" para sua imagem.
- Após efetuar qualquer mudança rode o seguinte comando no terminal : gcc esteganografia.c -o esteganografia -lpng > output.txt
- E para rodar o programa e ver funcionado, basta rodar o seguinte comando: ./esteganografia > output.txt
