from tensorflow.keras.datasets import mnist
import os
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
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

# wyświetlenie zaimportowanego zbioru
chosen_imgs = {}
for img, label in zip(x_train, y_train):
	if label not in chosen_imgs:
		chosen_imgs[label] = img
	if len(chosen_imgs) == 10:
		break

fig, axes = plt.subplots(2, 5, figsize=(10, 5))
axes = axes.flatten()

for idx in range(10):
	img = chosen_imgs[idx]
	axes[idx].imshow(chosen_imgs[idx], cmap='gray')
	axes[idx].set_title(f"number: {idx}")
	axes[idx].axis('off')

plt.tight_layout()
plt.show()

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
model = Sequential()
model.add(Dense(units=128, input_shape=(784,), activation='relu'))
model.add(Dense(units=128, activation='relu'))
model.add(Dropout(0.25))
model.add(Dense(units=num_classes, activation='softmax'))

# kompilacja modelu
model.compile(
	loss='categorical_crossentropy',
	optimizer='adam',
	metrics=['acc', 'precision', 'recall']
)
model.summary()

# trenowanie modelu
train = model.fit(
	x=x_train, 
	y=y_train, 
	batch_size=512, 
	epochs=10
)

# wyświetlenie statystyk treningu
acc = train.history['acc']
loss = train.history['loss']
precision = train.history['precision']
recall = train.history['recall']

fig, ax1 = plt.subplots()
ax2 = ax1.twinx()

ax1.set_xlabel('epoka')
ax1.set_ylabel('accuracy / precision / recall')
ax2.set_ylabel('loss')

ax1.plot(range(1, len(acc) + 1), acc, label='accuracy')
ax1.plot(range(1, len(precision) + 1), precision, label='precision')
ax1.plot(range(1, len(recall) + 1), recall, label='recall')
ax2.plot(range(1, len(loss) + 1), loss, label='loss')

fig.legend()
plt.title('training statistics')
plt.tight_layout()
plt.show()

# testowanie na zbiorze MNIST
print("testing on MNIST dataset:")
loss, acc, precision, recall = model.evaluate(x_test, y_test)

print(f"accuracy: {acc*100:.2f}%")
print(f"loss: {loss*100:.2f}%")
print(f"precision: {precision*100:.2f}%")
print(f"recall: {recall*100:.2f}%")

y_pred_prob = model.predict(x_test)
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

# testowanie na własnym zbiorze
print("testing on my dataset:")
loss, acc, precision, recall = model.evaluate(x_my, y_my)

print(f"accuracy: {acc*100:.2f}%")
print(f"loss: {loss*100:.2f}%")
print(f"precision: {precision*100:.2f}%")
print(f"recall: {recall*100:.2f}%")

y_pred_prob = model.predict(x_my)
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