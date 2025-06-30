const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');

const userSchema = new mongoose.Schema({
	nickname: {
		type: String,
		required: true,
		unique: true,
		trim: true,
		minLength: 3
	},

	email: {
		type: String,
		required: true,
		unique: true,
		trim: true,
		match: [/.+@.+\..+/, 'Podaj poprawny adres email.']
	},

	password: {
		type: String,
		required: true,
		minLength: 8
	},

	role: {
		type: String,
		enum: ['user', 'admin'],
		default: 'user'
	}
}, {
	timestamps: true // automatycznie dodaje pol createdAt, updatedAt
});

// hashuje hasło przy każdej zmianie pola password
userSchema.pre('save', async function(next) {
	if (!this.isModified('password')) return next();
	try {
		this.password = await bcrypt.hash(this.password, 10);
		next();
	} catch (err) {
		next(err);
	}
});

// porownanie zahashowanego hasła z wpisanym
userSchema.methods.comparePassword = function(plain) {
	return bcrypt.compare(plain, this.password);
};

module.exports = mongoose.model('User', userSchema);