import React, {useEffect, useState, useContext} from 'react';
import {useParams, useNavigate} from 'react-router-dom';
import {apiRequest} from '../api/client';
import ReviewList from '../components/ReviewList';
import ReviewForm from '../components/ReviewForm';
import {AuthContext} from '../contexts/AuthContext';
import NotFoundPage from './NotFoundPage'

export default function FilmDetailPage() {
	const {id} = useParams();
	const navigate = useNavigate();
	const {user} = useContext(AuthContext);
	const [film, setFilm] = useState(null);
	const [reviews, setReviews] = useState([]);
	const [error, setError] = useState('');
	const [editing, setEditing] = useState(false);
	const [editData, setEditData] = useState({name: '', genre: '', releaseYear: ''});
	const [notFound, setNotFound] = useState(false);

	const load = () => {
		apiRequest(`/films/${id}`)
			.then(f => {
				setFilm(f);
				setEditData({name: f.name, genre: f.genre, releaseYear: f.releaseYear});
			})
			.catch(err => {
				if (err.status === 404) {
					setNotFound(true);
					return;
				}
				setError(err.message);
			});
		
		apiRequest(`/reviews/film/${id}`)
			.then(res => setReviews(res.data || []))
			.catch(err => {
				if (err.status === 404) {
					setNotFound(true);
					return;
				}
				setError(err.message);
				setReviews([]);
			});
	};
	if (notFound) return <NotFoundPage />;

	useEffect(load, [id]);

	const handleDelete = async () => {
		try {
			await apiRequest(`/films/${id}`, {method: 'DELETE', auth: true});
				navigate('/');
		} catch (err) {setError(err.message);}
	};

	const handleEditChange = e => {
		const {name, value} = e.target;
		setEditData(d => ({...d, [name]: value}));
	};

	const handleEditSubmit = async e => {
		e.preventDefault();
		try {
			await apiRequest(`/films/${id}`, {
				method: 'PATCH',
				auth: true,
				body: {
					name: editData.name,
					genre: editData.genre,
					releaseYear: Number(editData.releaseYear)
				}
			});
			setEditing(false);
			load();
		} catch (err) {setError(err.message);}
	};

	if (error) return <NotFoundPage />;
	if (!film) return <p>Ładowanie</p>;

	return (
		<div>
			{!editing 
				? (
					<>
						<h2>{film.name}</h2>
						<div class="film-details">
							<p>{film.genre}, {film.releaseYear}</p>
							<p>{film.description}</p>
						</div>
						<div class="admin-panel">
							{user?.role === 'admin' && (
								<>
									<button onClick={() => setEditing(true)}>Edytuj</button>
									<button onClick={handleDelete}>Usuń</button>
								</>
							)}
						</div>
					</>
				) : (
					<form class="edit-form" onSubmit={handleEditSubmit}>
						<h3>Edytuj film</h3>
						<input
							name="name"
							value={editData.name}
							onChange={handleEditChange}
							required
						/>
						<input
							name="genre"
							value={editData.genre}
							onChange={handleEditChange}
							required
						/>
						<input
							name="releaseYear"
							type="number"
							value={editData.releaseYear}
							onChange={handleEditChange}
							required
						/>
						<button type="submit">Zapisz</button>
						<button type="button" onClick={() => setEditing(false)}>Anuluj</button>
					</form>
				)
			}
			<h3>Recenzje</h3>

			<div class="film-list">
				<ReviewList reviews={reviews} onDeleted={load} />
				{user && <ReviewForm filmId={id} onSubmitted={load} />}
			</div>

		</div>
	);
}