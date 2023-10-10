import cv2
import numpy as np
import tensorflow as tf

# Carregar o modelo pré-treinado
model = tf.keras.models.load_model('coca_cola_model.h5')

# Função para pré-processar a imagem
def preprocess_image(image):
    image = cv2.resize(image, (224, 224))
    image = image / 255.0
    image = np.expand_dims(image, axis=0)
    return image

# Função para realizar a inferência do modelo na imagem
def predict_image(image):
    processed_image = preprocess_image(image)
    prediction = model.predict(processed_image)
    return prediction

# Carregar a imagem de teste
image_path = 'coca_cola_test.jpg'
image = cv2.imread(image_path)

# Realizar a predição na imagem
prediction = predict_image(image)

# Verificar se a predição corresponde a uma lata de Coca-Cola
if prediction > 0.5:
    print("A imagem contém uma lata de Coca-Cola.")
else:
    print("A imagem não contém uma lata de Coca-Cola.")
    
    # Carregar a imagem de teste
image_path = 'coca_cola_test2.jpg'
image = cv2.imread(image_path)

# Realizar a predição na imagem
prediction = predict_image(image)

# Verificar se a predição corresponde a uma lata de Coca-Cola
if prediction > 0.5:
    print("A imagem contém uma lata de Coca-Cola.")
else:
    print("A imagem não contém uma lata de Coca-Cola.")