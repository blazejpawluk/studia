import React, { useEffect, useState, useContext } from 'react';
import {apiRequest} from '../api/client';
import FilmCard from '../components/FilmCard';
import {AuthContext} from '../contexts/AuthContext';

export default function FilmListPage() {
	const [films, setFilms] = useState([]);
	const [error, setError] = useState('');
	const [newFilm, setNewFilm] = useState({name: '', genre: '', releaseYear: ''});
	const {user} = useContext(AuthContext);

	const [page, setPage] = useState(1);
	const [limit, setLimit] = useState(10);
	const [pendingLimit, setPendingLimit] = useState(10);
	const [totalPages, setTotalPages] = useState(1);

	const [filterGenre, setFilterGenre] = useState('');
	const [filterYear, setFilterYear] = useState('');
	const [pendingFilterGenre, setPendingGenre] = useState('');
	const [pendingFilterYear, setPendingYear] = useState('');
	const [sort, setSort] = useState('');
	const [pendingSort, setPendingSort] = useState('');

	const loadFilms = () => {
		const params = new URLSearchParams({
			page, limit,
			...(filterGenre && {genre: filterGenre}),
			...(filterYear && {releaseYear: filterYear}),
			...(sort && {sort})
		});
		apiRequest(`/films?${params.toString()}`)
		.then(res => {
			setFilms(res.data || []);
			setTotalPages(res.meta.pages || 1);
		})
		.catch(err => setError(err.message));
	};

	useEffect(loadFilms, [page, limit, filterGenre, filterYear, sort]);

	const handleChangeNew = e => {
		const { name, value } = e.target;
		setNewFilm(f => ({ ...f, [name]: value }));
	};

	const handleSubmitNew = async e => {
		e.preventDefault();
		try {
			await apiRequest('/films', {
				method: 'POST', auth: true,
				body: {
					name: newFilm.name,
					genre: newFilm.genre,
					releaseYear: Number(newFilm.releaseYear)
				}
			});
			setNewFilm({name: '', genre: '', releaseYear: ''});
			loadFilms();
		} catch (err) {setError(err.message);}
	};

	const handlePrev = () => page > 1 && setPage(p => p - 1);
	const handleNext = () => page < totalPages && setPage(p => p + 1);
	const applyLimit = () => {setLimit(pendingLimit); setPage(1);};

	const applyFilters = () => {
		setFilterGenre(pendingFilterGenre);
		setFilterYear(pendingFilterYear);
		setSort(pendingSort);
		setPage(1);
	};

  	if (error) return <h2>{error}</h2>;

	return (
		<div>
		<h2>Filmy</h2>

		{user?.role === 'admin' && (
			<form class="film-form" onSubmit={handleSubmitNew}>
				<h3>Dodaj film</h3>
				<input name="name" placeholder="Tytuł" value={newFilm.name}
						onChange={handleChangeNew} required />
				<input name="genre" placeholder="Gatunek" value={newFilm.genre}
						onChange={handleChangeNew} required />
				<input name="releaseYear" type="number" placeholder="Rok"
						value={newFilm.releaseYear} onChange={handleChangeNew} required />
				<button type="submit">Dodaj</button>
				<hr></hr>
			</form>
		)}

		<h3>Filtruj i sortuj</h3>
		<div class="sort-form">
			<input
				placeholder="Gatunek"
				value={pendingFilterGenre}
				onChange={e => setPendingGenre(e.target.value)}
			/>
			<input
				type="number"
				placeholder="Rok"
				value={pendingFilterYear}
				onChange={e => setPendingYear(e.target.value)}
			/>
			<select
				value={pendingSort}
				onChange={e => setPendingSort(e.target.value)}
			>
				<option value="">Brak sortowania</option>
				<option value="name">Nazwa ↑</option>
				<option value="-name">Nazwa ↓</option>
				<option value="releaseYear">Rok ↑</option>
				<option value="-releaseYear">Rok ↓</option>
			</select>
			<button onClick={applyFilters}>Zastosuj filtry</button>
		</div>

		<div class="film-list">
			{films.map(f => <FilmCard key={f._id} film={f} />)}
			{films.length === 0 && <p>Brak filmów na tej stronie.</p>}
		</div>

		<div className="pagination">
			<div class="vertical">
				<label>
					Limit:
					<input
						type="number"
						min="1"
						value={pendingLimit}
						onChange={e => setPendingLimit(Number(e.target.value) || 1)}
					/>
				</label>
				<button onClick={applyLimit}>Zastosuj</button>
			</div>
			<div class="vertical">
				<button onClick={handlePrev} disabled={page === 1}>« Poprzednia</button>
				<span>Strona {page} / {totalPages}</span>
				<button onClick={handleNext} disabled={page === totalPages}>Następna »</button>
			</div>
		</div>
		</div>
	);
}