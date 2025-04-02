# Błażej Pawluk, 279738
# zadanie 1

import numpy as np
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.optimizers import Adam
from sklearn.metrics import precision_score, recall_score

# Ładowanie zbioru danych MNIST (60000 treningowych + 10000 testowych = 70000 cyfr)
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Normalizacja danych - przeskalowanie wartości pikseli do zakresu [0, 1]
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

# Konwersja etykiet
num_classes = 10 # liczba klas
y_train_cat = to_categorical(y_train, num_classes)
y_test_cat = to_categorical(y_test, num_classes)
# zmiana 3 na [0, 0, 0, 1, 0, 0, 0, 0, 0, 0]

# Budowa modelu sieci neuronowej
model = Sequential([
    Flatten(input_shape=(28, 28)), # zamiana obrazu 28x28 na jednowymiarowy 1x784
    Dense(128, activation='relu'),
    Dense(num_classes, activation='softmax') # ostatnia warstwa z 10 neuronami
])

# Kompilacja modelu
model.compile(optimizer=Adam(),
              loss='categorical_crossentropy',
              metrics=['accuracy'])

# Trenowanie modelu
model.fit(x_train, y_train_cat, epochs=10, batch_size=128, verbose=1)

# Ewaluacja modelu na zbiorze testowym
test_loss, test_accuracy = model.evaluate(x_test, y_test_cat, verbose=0)
print(f"Dokładność (accuracy) na zbiorze testowym: {test_accuracy:.4f}")

# Predykcja etykiet na zbiorze testowym
y_pred_prob = model.predict(x_test)
y_pred = np.argmax(y_pred_prob, axis=1)

# Obliczenie precyzji i czułości (używając uśredniania 'weighted')
precision = precision_score(y_test, y_pred, average='weighted')
recall = recall_score(y_test, y_pred, average='weighted')

print(f"Precyzja (precision): {precision:.4f}")
print(f"Czułość (recall): {recall:.4f}")
