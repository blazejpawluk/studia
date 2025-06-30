const User = require('../models/User');

// GET /api/users?page=&limit= (admin only)
exports.getAllUsers = async (req, res, next) => {
	try {
		const {role} = req.user;
		if (role !== 'admin') return res.status(403).json({message: 'Brak uprawnień.'});

		const page = parseInt(req.query.page) || 1;
		const limit = parseInt(req.query.limit) || 10;
		const skip = (page - 1) * limit;

		const [total, users] = await Promise.all([
			User.countDocuments(),
			User.find()
				.select('-password')
				.skip(skip)
				.limit(limit)
		]);

		res.json({
			data: users,
			meta: {total, page, pages: Math.ceil(total/limit)}
		});
	} catch (err) {
		next(err);
	}
}

// GET /api/users/:id (admin or logged user)
exports.getUserById = async (req, res, next) => {
	try {
		const {id: userId, role} = req.user;
		const {id} = req.params;

		if (role !== 'admin' && userId !== id) return res.status(403).json({message: 'Brak uprawnień.'});

		const user = await User.findById(id).select('-password');
		if (!user) return req.status(404).json({message: 'Użytkownik nie znaleziony'});
		res.json(user);
	} catch (err) {
		next(err);
	}
}

// PUT /api/users/:id (admin or logged user)
exports.editUser = async (req, res, next) => {
	try {
		const { id } = req.params;
		if (req.user.role !== 'admin' && req.user.id !== id) return res.status(403).json({ message: 'Brak uprawnień' });

		if (req.user.role !== 'admin' && req.body.role) delete req.body.role;
	
		if (req.body.password) {
			const user = await User.findById(id);
			if (!user) return res.status(404).json({ message: 'Użytkownik nie istnieje' });
			user.nickname = req.body.nickname ?? user.nickname;
			user.email = req.body.email ?? user.email;
			user.password = req.body.password;
			if (req.user.role === 'admin' && req.body.role) user.role = req.body.role;
			const saved = await user.save();
			const safe = saved.toObject();
			delete safe.password;
			return res.json(safe);
		}
	
		const updated = await User.findByIdAndUpdate(
			id,
			{$set: req.body},
			{new: true, runValidators: true}
		).select('-password');
		if (!updated) return res.status(404).json({ message: 'Użytkownik nie istnieje' });
		return res.json(updated);
	} catch (err) {
		next(err);
	}
}

// DELETE /api/users/:id (admin or logged user)
exports.removeUser = async (req, res, next) => {
	try {
		const {id: userId, role} = req.user;
		const {id} = req.params;

		const user = await User.findById(id);
		if (!user) return res.status(404).json({message: 'Użytkownik nie znaleziony.'});

		if (role !== 'admin' && userId !== id) return res.status(403).json({message: 'Brak uprawnień.'});

		await user.deleteOne();
		res.status(204).end();
	} catch (err) {
		next(err);
	}
}