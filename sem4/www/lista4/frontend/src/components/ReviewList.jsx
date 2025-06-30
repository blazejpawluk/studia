import React, {useContext} from 'react';
import {AuthContext} from '../contexts/AuthContext';
import {apiRequest} from '../api/client';

export default function ReviewList({reviews, onDeleted}) {
	const {user} = useContext(AuthContext);

	if (!Array.isArray(reviews)) return <p>Brak recenzji do wyświetlenia.</p>

	const remove = async id => {
		try {
			await apiRequest(`/reviews/${id}`, {method: 'DELETE', auth: true});
			onDeleted();
		} catch {}
	};

	return (
		<ul class="film-list">
			{reviews.map(r => (
				<li class="card" key={r._id}>
					{r.user.nickname} ({r.rating}/10): {r.description}
					{user && (user.role === 'admin' || user.id === r.user._id) && (
						<button onClick={() => remove(r._id)}>Usuń</button>
					)}
				</li>
			))}
		</ul>
	);
}