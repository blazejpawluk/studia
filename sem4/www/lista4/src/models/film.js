const mongoose = require('mongoose')

const filmSchema = new mongoose.Schema({
	name: {
		type: String, 
		required: true
	},

	description: {
		type: String
	},

	genre: {
		type: String,
		enum: ['action', 'comedy', 'documentary', 'horror', 'science-fiction', 'other', 'undefined'],
		default: 'undefined'
	},

	releaseYear: {
		type: Number,
		min: 1800,
		max: new Date().getFullYear()
	}
}, {
	timestamps: true
});

module.exports = mongoose.model('Film', filmSchema);