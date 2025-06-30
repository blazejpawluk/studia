import React, {createContext, useState, useEffect} from 'react';
import {apiRequest} from '../api/client';
import {useNavigate} from 'react-router-dom';

export const AuthContext = createContext();

export function AuthProvider({children}) {
	const [user, setUser] = useState(() => {
		const raw = localStorage.getItem('user');
		return raw ? JSON.parse(raw) : null;
	});
	const navigate = useNavigate();

	useEffect(() => {
		if (user) localStorage.setItem('user', JSON.stringify(user));
		else localStorage.removeItem(user);
	}, [user]);

	const login = async(email, password) => {
		const res = await apiRequest('/auth/login', {
			method: 'POST',
			body: {email, password}
		});
		localStorage.setItem('token', res.token);
		setUser(res.user);
		navigate('/');
	}

	const register = async(nickname, email, password) => {
		const res = await apiRequest('/auth/register', {
			method: 'POST',
			body: {nickname, email, password}
		});
		localStorage.setItem('token', res.token);
		setUser(res.user);
		navigate('/');
	}

	const logout = () => {
		localStorage.removeItem('token');
		setUser(null);
		navigate('/login');
	}

	return (
		<AuthContext.Provider value={{user, setUser, login, register, logout}}>
			{children}
		</AuthContext.Provider>
	)
}