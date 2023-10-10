import h5py
from PIL import Image
import numpy as np

# Converte a imagem para uma matriz numpy
matriz_imagem = np.array(Image.open('C:\\Users\\thuli\\Documents\\Estágio\\Projeto\\1.0\\Lata_Coca_Cola.JPG'))

# Cria o arquivo HDF5
arquivo_h5 = h5py.File('imagem.h5', 'w')

# Cria o dataset dentro do arquivo HDF5 e salva a matriz da imagem
arquivo_h5.create_dataset('imagem', data=matriz_imagem)

# Fecha o arquivo HDF5
arquivo_h5.close()

print("Arquivo .h5 criado com sucesso.")
