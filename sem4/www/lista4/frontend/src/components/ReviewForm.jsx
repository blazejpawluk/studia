import React, {useState} from 'react';
import {apiRequest} from '../api/client';

export default function ReviewForm({filmId, onSubmitted}) {
	const [rating, setRating] = useState(5);
	const [description, setDescription] = useState('');
	const [error, setError] = useState('');

	const submit = async e => {
		e.preventDefault();
		try {
			await apiRequest(`/reviews/film/${filmId}`, {
				method: 'POST',
				auth: true,
				body: {rating, description}
			});
			setDescription('');
			onSubmitted();
		} catch (err) {setError(err.message);}
	}
	
	return (
		<form class="edit-form" onSubmit={submit}>
			{error && <p>error</p>}
			<input
				type="number"
				min="0"
				max="10"
				value={rating}
				onChange={e => setRating(+e.target.value)}
			/>
			<textarea
				value={description}
				onChange={e => setDescription(e.target.value)}
				placeholder="Twoja recenzja"
			/>
			<button type="submit">Dodaj recenzję</button>
		</form>
	);
}