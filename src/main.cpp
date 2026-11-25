{
	"geode": "6.0.0",
	"gd": {
		"mac": "*"
	},
	"id": "tuusuario.gdlitemac",
	"name": "GD Lite (Mac)",
	"version": "v1.0.0",
	"developer": "TuUsuario",
	"description": "Ligero ajuste de rendimiento para Geometry Dash en macOS: menos coste de partículas y mejor prioridad de hilo.",
	"tags": [
		"performance",
		"utility"
	],
	"settings": {
		"reduce-particles": {
			"name": "Reducir coste de partículas",
			"description": "Actualiza los sistemas de partículas solo una de cada N frames dentro de un nivel. Desactivado por defecto para evitar conflictos con otros mods que usen partículas.",
			"type": "bool",
			"default": false
		},
		"particle-skip": {
			"name": "Actualizar partículas cada N frames",
			"description": "2 = la mitad de actualizaciones, 3 = un tercio, etc.",
			"type": "int",
			"default": 2,
			"min": 1,
			"max": 4,
			"control": {
				"slider": true
			}
		},
		"prevent-app-nap": {
			"name": "Desactivar App Nap",
			"description": "Pide a macOS que no limite temporizadores ni CPU del juego. Requiere reiniciar el juego.",
			"type": "bool",
			"default": true
		},
		"high-priority": {
			"name": "Hilo principal con prioridad alta",
			"description": "Marca el hilo principal como USER_INTERACTIVE (en Apple Silicon favorece los núcleos de rendimiento). Requiere reiniciar el juego.",
			"type": "bool",
			"default": true
		}
	}
}
