from tensorflow.keras.datasets import mnist
import os
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
from tensorflow.keras.utils import to_categorical
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score
from sklearn.metrics import confusion_matrix
import seaborn as sb

num_classes = 10

# importowanie danych
(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_my = np.empty([30, 28, 28])
y_my = np.array([i for i in range(num_classes) for _ in range(3)])

i = 0
for digit in range (0, num_classes):
	for number in range(1, 4):
		image = Image.open(f"myDigits/{digit}-{number}.png").convert('L')
		image = image.resize((28, 28))
		x_my[i] = np.array(image)
		i += 1

# formatowanie danych
x_train = x_train.astype('float32') / 255.0
x_train = x_train.reshape(x_train.shape[0], -1)

x_test = x_test.astype('float32') / 255.0
x_test = x_test.reshape(x_test.shape[0], -1)

x_my /= 255.0
x_my = x_my.reshape(x_my.shape[0], -1)

y_train = to_categorical(y_train, num_classes)
y_test = to_categorical(y_test, num_classes)
y_my = to_categorical(y_my, num_classes)

# tworzenie modelu
model = RandomForestClassifier(n_estimators=10, random_state=42)

# trenowanie modelu
model.fit(x_train, y_train)

# testowanie na zbiorze MNIST
print("testing on MNIST dataset:")
y_pred_prob = model.predict(x_test)

acc = accuracy_score(y_test, y_pred_prob)
precision = precision_score(y_test, y_pred_prob, average='macro')
recall = recall_score(y_test, y_pred_prob, average='macro')

print(f"accuracy: {acc*100:.2f}%")
print(f"precision: {precision*100:.2f}%")
print(f"recall: {recall*100:.2f}%")

y_pred = np.argmax(y_pred_prob, axis=1)
y_real = np.argmax(y_test, axis=1)
conf_matrix = confusion_matrix(y_real, y_pred)

fig, ax = plt.subplots(figsize=(15, 10))
ax = sb.heatmap(conf_matrix, annot=True, fmt='d', ax=ax)
ax.set_xlabel('prediction')
ax.set_ylabel('real')
ax.set_title('confusion matrix (testing on MNIST dataset)')

plt.tight_layout()
plt.show()

# testowanie na zbiorze MNIST
print("testing on my dataset:")
y_pred_prob = model.predict(x_my)

acc = accuracy_score(y_my, y_pred_prob)
precision = precision_score(y_my, y_pred_prob, average='macro')
recall = recall_score(y_my, y_pred_prob, average='macro')

print(f"accuracy: {acc*100:.2f}%")
print(f"precision: {precision*100:.2f}%")
print(f"recall: {recall*100:.2f}%")

y_pred = np.argmax(y_pred_prob, axis=1)
y_real = np.argmax(y_my, axis=1)
conf_matrix = confusion_matrix(y_real, y_pred)

fig, ax = plt.subplots(figsize=(15, 10))
ax = sb.heatmap(conf_matrix, annot=True, fmt='d', ax=ax)
ax.set_xlabel('prediction')
ax.set_ylabel('real')
ax.set_title('confusion matrix (testing on my dataset)')

plt.tight_layout()
plt.show()