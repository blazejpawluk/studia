const Review = require('../models/Review');
const Film = require('../models/Film');

// GET /api/reviews/film/:filmId
exports.getReviewByFilm = async (req, res, next) => {
	try {
		const {filmId} = req.params;

		const film = await Film.findById(filmId);
		if (!film) return res.status(404).json({message: 'Film nie znaleziony.'});

		const reviews = await Review.find({film: filmId})
			.populate('user', 'nickname')
			.sort({createdAt: -1});

		res.json({data:reviews});
	} catch (err) {
		next(err);
	}
}

// POST /api/reviews/film/:filmId
exports.addReview = async (req, res, next) => {
	try {
		const {filmId} = req.params;
		const {rating, description} = req.body;
		const userId = req.user.id;

		const film = await Film.findById(filmId);
		if (!film) return res.status(404).json({message: 'Film nie znaleziony.'});

		const review = new Review({
			user: userId, 
			film: filmId,
			rating,
			description
		});
		const saved = await review.save();

		await saved.populate('user', 'nickname');

		res.status(201).json(saved);
	} catch (err) {
		next(err);
	}
}

// DELETE /api/reviews/:id (admin, author)
exports.removeReview = async (req, res, next) => {
	try {
		const {id: reviewId} = req.params;
		const {id: userId, role} = req.user;

		const review = await Review.findById(reviewId);
		if (!review) return res.status(404).json({message: 'Recenzja nie znaleziona.'});

		if (role !== 'admin' && review.user.toString() !== userId) return res.status(403).json({message: 'Brak uprawnień do usunięcia tej recenzji.'});
		
		await review.deleteOne();
		res.status(204).end();
	} catch (err) {
		next(err);
	}
}