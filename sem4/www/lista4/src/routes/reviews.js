const express = require('express');
const router = express.Router();
const review = require('../controllers/review');
const {verifyToken} = require('../middleware/auth');

router.get('/film/:filmId', review.getReviewByFilm);
router.post('/film/:filmId', verifyToken, review.addReview);
router.delete('/:id', verifyToken, review.removeReview);

module.exports = router;