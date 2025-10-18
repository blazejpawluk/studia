import React, {useEffect, useState, useContext} from 'react';
import {apiRequest} from '../api/client';
import {AuthContext} from '../contexts/AuthContext';

export default function UserListPage() {
	const {user} = useContext(AuthContext);
	const [users, setUsers] = useState([]);
	const [error, setError] = useState('');

	const loadUsers = () => {
		apiRequest('/users', { auth: true })
		.then(res => setUsers(res.data || []))
		.catch(err => setError(err.message));
	};

	useEffect(loadUsers, []);

	const handleDelete = async id => {
		if (!window.confirm('Usunąć tego użytkownika?')) return;
		try {
			await apiRequest(`/users/${id}`, { method: 'DELETE', auth: true });
			loadUsers();
		} catch (err) {setError(err.message);}
	};

	if (error) return <h2>{error}</h2>;
	if (user.role !== 'admin') return <p>Brak dostępu</p>;

	return (
		<div>
			<h2>Lista użytkowników</h2>
			{users.length === 0 ? (
				<p>Brak użytkowników.</p>
			) : (
				<ul class="film-list">
					{users.map(u => (
						<li class="card" key={u.id || u._id}>
							{u.nickname} ({u.email}) - {u.role}
							<button onClick={() => handleDelete(u.id || u._id)}>
								Usuń konto
							</button>
						</li>
					))}
				</ul>
			)}
		</div>
	);
}