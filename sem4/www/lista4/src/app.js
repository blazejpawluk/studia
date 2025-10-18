require('dotenv').config();
const express = require('express');
const cors = require('cors');
const path = require('path');

const authRoutes = require('./routes/auth');
const userRoutes = require('./routes/users');
const filmRoutes = require('./routes/films');
const reviewRoutes = require('./routes/reviews');
const errorHandler = require('./middleware/errorHandler');

const app = express();

app.use(cors());
app.use(express.json());

app.use('/api/auth', authRoutes);
app.use('/api/users', userRoutes);
app.use('/api/films', filmRoutes);
app.use('/api/reviews', reviewRoutes);

app.use(express.static(path.join(__dirname, '../frontend')));
app.use((req, res) => res.sendFile(path.join(__dirname, '../frontend/index.html')));

app.use(errorHandler);

module.exports = app;