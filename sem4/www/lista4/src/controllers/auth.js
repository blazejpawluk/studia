const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const User = require('../models/User');

// POST /api/auth/register
exports.register = async (req, res, next) => {
	try {
		const {nickname, email, password} = req.body;

		const existing = await User.findOne({email}, {nickname});
		if (existing) return res.status(400).json({message: 'Email lub nick jest już zajęty.'});

		const user = new User({
			nickname, email, password, role: 'user'
		});

		const saved = await user.save();

		const token = jwt.sign(
			{id: saved._id.toString(), role: saved.role},
			process.env.JWT_SECRET,
			{expiresIn: '1d'}
		);

		res.status(201).json({
			message: 'Użytkownik zarejestrowany',
			token,
			user: {
				id: saved._id,
				nickname: saved.nickname,
				email: saved.email,
				role: saved.role
			}
		});
	} catch(err) {
		next(err);
	}
}

// POST api/auth/login
exports.login = async (req, res, next) => {
	try {
		const {email, password} = req.body;

		const user = await User.findOne({email});
		if (!user) return res.status(401).json({message: 'Nieprawidłowe dane logowania. (email)'});

		const match = await bcrypt.compare(password, user.password);
		if (!match) return res.status(401).json({message: 'Nieprawidłowe dane logowania. (hasło)'});

		const token = jwt.sign(
			{id: user._id.toString(), role: user.role},
			process.env.JWT_SECRET,
			{expiresIn: '1d'}
		);

		res.json({
			message: 'Zalogowano',
			token,
			user: {
				id: user._id,
				nickname: user.nickname,
				email: user.email,
				role: user.role
			}
		});
	} catch (err) {
		next(err);
	}
}