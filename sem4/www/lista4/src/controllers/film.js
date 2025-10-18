const Film = require('../models/Film');

// GET /api/films?page=&limit=&genre=&&releaseYear=&sort=
exports.getFilms = async (req, res, next) => {
	try {
		const page = parseInt(req.query.page) || 1;
		const limit = parseInt(req.query.limit) || 10;
		const skip = (page - 1) * limit;

		const filter = {};
		if (req.query.genre) filter.genre = req.query.genre;
		if (req.query.releaseYear) filter.releaseYear = req.query.releaseYear;

		const sort = {};
		if (req.query.sort) {
			req.query.sort.split(',').forEach(field => {
				if (field.startsWith('-')) sort[field.slice(1)] = -1;
				else sort[field] = 1;
			})
		}

		const [total, films] = await Promise.all([
			Film.countDocuments(filter),
			Film.find(filter)
				.sort(sort)
				.skip(skip)
				.limit(limit)
		]);

		res.json({
			data: films,
			meta: {total, page, pages: Math.ceil(total / limit)}
		});
	} catch (err) {
		next(err);
	}
}

// GET /api/films/:id
exports.getFilmById = async (req, res, next) => {
	try {
		const film = await Film.findById(req.params.id);
		if (!film) return req.status(404).json({message: 'Film nie znaleziony.'});
		res.json(film);
	} catch (err) {
		next(err);
	}
}

// POST /api/films (admin)
exports.addFilm = async (req, res, next) => {
	try {
		const {role} = req.user;
		if (role !== 'admin') return res.status(403).json({message: 'Brak uprawnień.'});

		const newFilm = new Film(req.body);
		const saved = await newFilm.save();
		res.status(201).json(saved);
	} catch (err) {
		next(err);
	}
}

// PATCH /api/films/:id (admin)
exports.editFilm = async (req, res, next) => {
	try {
		const {role} = req.user;
		if (role !== 'admin') return res.status(403).json({message: 'Brak uprawnień.'});

		const updated = await Film.findByIdAndUpdate(
			req.params.id, 
			{$set: req.body},
			{new: true, runValidators: true}
		);
		if (!updated) return res.status(404).json({message: 'Film nie znaleziony.'});
		res.json(updated);
	} catch (err) {
		next(err);
	}
}

// DELETE /api/films/:id (admin)
exports.removeFilm = async (req, res, next) => {
	try {
		const {role} = req.user;
		if (role !== 'admin') return res.status(403).json({message: 'Brak uprawnień.'});

		const deleted = await Film.findByIdAndDelete(req.params.id);
		if (!deleted) return res.status(404).json({message: 'Film nie znaleziony.'});
		res.status(204).end();
	} catch (err) {
		next(err);
	}
}