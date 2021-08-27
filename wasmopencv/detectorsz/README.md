

1. Objetivo

A partir da mesmo código fonte, comparar o tempo de execução no WASM versus compilação nativa para windows 10.

2. Saidas

Número de faces e olhos detectados por frame.

3. Metricas

Tempo de execução das instruçoes de processamento de imagem

4. Parametros

workload, dataset (small/large), 

Aplicação para medir o tempo de processamento do código de identificação de faces do opencv.


Especificação

Sistema deve rocessar todos os frames do vide converter para uma resolução padrão de 512 de largupra por 
para videos com escala menor deve ser aplicada uma traformação utilizando 

Para validar foram identificados o seguinde conjunto de dados de teste que foram extraidos
videos publicado no site you tube  foi fetio o download em v=formato mp4 e ctalogado 
a a resolução , FPS e link de origem do vieo. Para download voif utilizada a ferramenta.

https://www.youtube.com/watch?v=tznWpTAV41M
https://www.youtube.com/watch?v=vQtLX6pW5eA
https://www.youtube.com/watch?v=EWUdGRAwUpY
https://www.youtube.com/watch?v=JoWIjjZ6a-k
https://www.youtube.com/watch?v=de2Hsvxaf8M
https://www.youtube.com/watch?v=ESjTlD606aQ
https://www.youtube.com/watch?v=tGNBdjVO04Y
https://www.youtube.com/watch?v=5XVCf-CAEPk
https://www.youtube.com/watch?v=AZ4tesVagso
https://www.youtube.com/watch?v=RuL5jVqc4Tg


https://ytdl-org.github.io/youtube-dl/index.html



Experimento 1 

Report:LOG_FACE_DETECT_DATASET_1_SMALL_WINDOWS_10_WIN32.csv
Dataset: DATASET_1
Workload: FACE_DETECT
Total of frames : 3915
Total of frames processeds: 744
Total time: 340460

Report:LOG_FACE_DETECT_DATASET_1_MEDIUM_WINDOWS_10_WIN32.csv
Workload: FACE_DETECT
Dataset: DATASET_1
System: WINDOWS_10_WIN32
Total of frames : 3915
Total of frames processeds: 652
Total time (ms): 364988

Report:LOG_FACE_DETECT_DATASET_1_LARGE_WINDOWS_10_WIN32.csv
Workload: FACE_DETECT
Dataset: DATASET_1
System: WINDOWS_10_WIN32
Total of frames : 3915
Total of frames processeds: 237
Total time (ms): 451438


