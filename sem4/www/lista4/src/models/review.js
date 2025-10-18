const mongoose = require('mongoose');

const reviewSchema = new mongoose.Schema({
	user: {
		type: mongoose.Schema.Types.ObjectId,
		ref: 'User',
		required: true
	},

	film: {
		type: mongoose.Schema.Types.ObjectId,
		ref: 'Film',
		required: true
	},

	rating: {
		type: Number,
		required: true,
		min: 0,
		max: 10
	}, 

	description: {
		type: String
	}
}, {
	timestamp: true
});

module.exports = mongoose.model('Review', reviewSchema);