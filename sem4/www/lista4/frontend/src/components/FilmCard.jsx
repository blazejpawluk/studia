import React from 'react';
import {Link} from 'react-router-dom';

export default function FilmCard({film}) {
	return (
		<div class="card">
			<h3>
				<Link to={`/films/${film._id}`}>{film.name}</Link>
			</h3>
			<p>{film.genre}, {film.releaseYear}</p>
		</div>
	);
}