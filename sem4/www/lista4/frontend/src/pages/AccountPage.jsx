import React, {useState, useContext, useEffect} from 'react';
import {AuthContext} from '../contexts/AuthContext';
import {apiRequest} from '../api/client';

export default function AccountPage() {
	const {user, logout, setUser} = useContext(AuthContext);
	const [form, setForm] = useState({nickname: '', email: '', password: ''});
	const [msg, setMsg] = useState('');

	useEffect(() => {
		if (user) setForm({ nickname: user.nickname, email: user.email, password: '' });
	}, [user]);

	const handleChange = e => {
		const { name, value } = e.target;
		setForm(f => ({...f, [name]: value}));
	};

	const handleSubmit = async e => {
		e.preventDefault();
		try {
			const data = {};
			if (form.nickname !== user.nickname) data.nickname = form.nickname;
			if (form.email !== user.email) data.email = form.email;
			if (form.password) data.password = form.password;

			const updated = await apiRequest(`/users/${user.id}`, {
				method: 'PUT',
				auth: true,
				body: data
			});
			setUser({
				id: updated._id,
				nickname: updated.nickname,
				email: updated.email,
				role: updated.role
			});
			setMsg('Zapisano zmiany');
			setForm(f => ({...f, password: ''}));
		} catch (err) {setMsg(err.message);}
	};

	const handleDeleteAccount = async () => {
		try {
			await apiRequest(`/users/${user.id}`, {
				method: 'DELETE',
				auth: true
			});
			logout();
		} catch (err) {setMsg(err.message);}
	};

	if (!user) return null;
	return (
		<form onSubmit={handleSubmit}>
			<h2>Moje konto</h2>
			{msg && <p>{msg}</p>}

			<div class="login-form">
				<label>
					Nick
					<input
						name="nickname"
						value={form.nickname}
						onChange={handleChange}
						required
					/>
				</label>
				<label>
					Email
					<input
						name="email"
						type="email"
						value={form.email}
						onChange={handleChange}
						required
					/>
				</label>
				<label>
					Nowe hasło
					<input
						name="password"
						type="password"
						value={form.password}
						onChange={handleChange}
					/>
				</label>
				<button type="submit">Zapisz</button>
				<button type="button" onClick={handleDeleteAccount}>Usuń konto i wyloguj</button>
			</div>
		</form>
	);
}