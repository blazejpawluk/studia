const express = require('express');
const router = express.Router();
const film = require('../controllers/film');
const {verifyToken} = require('../middleware/auth');

router.get('/', film.getFilms);
router.get('/:id', film.getFilmById);
router.post('/', verifyToken, film.addFilm);
router.patch('/:id', verifyToken, film.editFilm);
router.delete('/:id', verifyToken, film.removeFilm);

module.exports = router;