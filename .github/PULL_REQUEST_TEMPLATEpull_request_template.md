# 💪 Human Testing

<a href="https://www.notion.so/bonjourio/Review-a-PR-9a9d9c4f46b14dcdb109aba9ef9cbfac" target="_blank">GOOD REVIEW PRACTICES</a>

# Prérequis

- [ ] J'ai consulté [le fichier des good practices](https://www.notion.so/bonjourio/Review-a-PR-9a9d9c4f46b14dcdb109aba9ef9cbfac) pour review
- [ ] J'ai noté les actions manuelles pour la prochaine MEP dans le ticket de MEP (variable d'environnement, souscription pusher)
- [ ] Si j'ai modifié le format des data d'un OpenTok Stream name ou ajouté un name différent (salesRepSharing/prospectCamera/..), j'ai update les services qui sont liés (meetingAudioExtractor/recording/..)

# Tests de non régressions

* [J'ai fait une intégration](#jai-fait-une-intégration)
* [J'ai changé la configuration de Circle CI](#jai-changé-la-configuration-de-circle-ci)
* [Je fais une non régression de call](#je-fais-une-non-régression-de-call)
* [Je fais une non régression sur les intégrations](#je-fais-une-non-régression-sur-les-intégrations)
  * [Salesforce](#salesforce)
  * [Google Calendar](#google-calendar)
* [Je fais une non reg sur le meeting note templates](#je-fais-une-non-reg-sur-le-meeting-note-templates)
* [Je fais une non régression sur la sélection des devices](#je-fais-une-non-régression-sur-la-sélection-des-devices)
  * [Studio](#studio)
  * [Viewer](#viewer)
* [Je fais une non régression Manager](#je-fais-une-non-régression-manager)
  * [Call](#call)
  * [Comments](#comments)
  * [Transcript](#transcript)

## J'ai fait une intégration

- [ ] Mettre la capture d'écran de comparaison Invision/Résultat

## J'ai changé la configuration de Circle CI

- [ ] exécuter `npx @bonjourio/circleci-graph .circleci/config.yml` puis faire un render sur http://www.webgraphviz.com/
- [ ] exécuter `circleci config validate`
- [ ] Mettre une capture des steps CI

## Je fais une non régression de call

<p style="padding: 5px; background-color: #fff3cd">
💡 Pour faire le parcours de non régréssion il faut

- **être déloggué de l'application**
- **avoir l'application fermée**
- avoir démarré ngrok pour vérifier que le call lifecylce fonctionne ♻️

</p>

- [ ] 👨🏻‍💼 ETQSR, je lance Google Calendar et je crée un meeting qui contient @BonjourMeeting (dev) | #BonjourStaging (staging) | #BonjourPreprod (preprod)  en invitant `tools@bonjour.io`
- [ ] ETQDev, j'ouvre la boite mail de tools@bonjour.io
- [ ] 👨🏻‍💼 ETQSR, je lance l'application et je me Google Login
- [ ] 👨🏻‍💼 ETQSR, je vois bien le meeting dans ma liste des meetings
- [ ] 👩🏼‍💼 ETQTools@bonjour.io, je vois bien l'invitation, je garde les mails ouverts et vérifie que je recois bien le bon nombre d'invitations.
- [ ] 👨🏻‍💼 ETQSR, je clique sur 'Instant Call' pour lancer un meeting
- [ ] 👨🏻‍💼 ETQSR, j'écris une note
  - Je vois '... Editing' pendant 5 secondes puis '✔ Saved'
- [ ] 👨🏻‍💼 ETQSR, je clique sur 'Start call'
  - je vois 'Waiting for guests to join ...'
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données il n'y a pas de nouveau call</span>
- [ ] 👨🏻‍💼 ETQSR, je clique sur le bouton 'link' pour récupérer l'url du RDV
  - je vois la notification 'Meeting URL copied to clipboard'
- [ ] 👩🏼‍💼 ETQP, j'ouvre Safari pour copier l'url du meeting
- [ ] 👩🏼‍💼 ETQP, je clique sur l'icone 'gear' pour ouvrir la popup de choix de devices
- [ ] 👩🏼‍💼 ETQP, je clique sur 'Join meeting'
  - Je vois le sales rep.
  - Je vois le halo vert lorsqu'il y a du bruit sur 'ME' et sur le Sales Rep
  - Je peux resize la sidebar en mode landscape
  - Je vois que l'aspect ratio de la video du SR garde sont aspect ratio en portrait
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données un nouveau call a été créé sans date de fin</span>
  - [ ] ETQSR Je partage une application
  - [ ] ETQP Je vois l'application partagée
  - [ ] ETQSR Je stop le partage d'écran
  - [ ] ETQP Je partage mon écran
  - [ ] ETQSR Je vois l'application partagée
  - [ ] ETQP Je stop le partage d'écran
- [ ] 👩🏼‍💼 ETQP, je mute mon micro
- [ ] 👨🏻‍💼 ETQSR, je vois le micro rouge apparaître sur la vidéo du prospect
- [ ] 🧑🏽‍💼 ETQP2, j'ouvre un autre browser pour copier l'url du meeting
- [ ] 🧑🏽‍💼 ETQP2, je n'autorise pas les devices, et rejoins sans publier de flux.
- [ ] 🧑🏽‍💼 ETQP2, je vois bien les streams des deux autres attendees
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données il n'y a toujours qu'un seul call sans date de fin</span>
- [ ] 👨🏻‍💼 ETQSR, je clique sur le bouton 'End call'
- [ ] 👨🏻‍💼 ETQSR, je vois le save to salesforce si salesforce connecté
- [ ] 👨🏻‍💼 ETQSR, je vois le questionnaire de qualité
- [ ] 👨🏻‍💼 ETQSR, je vois le questionnaire de goal attainment
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données le call a une date de fin</span>
- [ ] 👨🏻‍💼 ETQSR, je retourne dans le call
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données un nouveau call a été créé sans date de fin</span>
- [ ] 🧑🏽‍💼 ETQP2, je clique sur le bouton 'End call' et je vois le questionnaire de qualité
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données il n'y a toujours qu'un seul call sans date de fin</span>
- [ ] 👩🏼‍💼 ETQP, je clique sur le bouton 'End call' et je vois le questionnaire de qualité
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données le call a une date de fin</span>
- [ ] 👨🏻‍💼 ETQSR, je clique sur le bouton 'End call' et je vois le questionnaire de qualité
  - [ ] <span style="color: #FF195A;">♻️ Dans la base de données les deux calls sont bien terminés</span>
- [ ] 👨🏻‍💼 ETQSR, je clique sur le tab Rec, j'ai bien un recording available.
- [ ] 👨🏻‍💼 ETQSR, je clique sur le bouton "Gear" en haut à droit et je me déloggue.

- [ ] 🚨 ETQDev, qui soummet la PR, je joue la non Reg Salesforce si la Feature Salesforce est impactée

## Je fais une non régression sur les intégrations

### Salesforce

Prérequis : Avoir un compte Salesforce connecté (+bonjourcanary)

- [ ] ETQSR, dans un meeting, je click sur le bouton salesforce
- [ ] ETQSR, Je choisis Deux records de types différents par autocompletion avec "tes" (match de nombreux record "test" en canary. 3 lettres minimum)
- [ ] ETQSR, Je soumets la sauvegarde en tant que notes et logcall
- [ ] ETQSR, Je vois une confirmation, je click sur le lien see results in salesforce
- [ ] ETQSR, Dans les deux onglets salesforce ouverts, je vois les notes et log call fraichement créés
- [ ] ETQSR, je ferme la pop; entre dans les settings et déconecte mon compte salesforce
- [ ] ETQSR, je reconnecte mon compte salesforce

### Google Calendar

#### Mise à jour des événements depuis le studio

- [ ] ETQSR, je lance l'application et je me Google Login
- [ ] ETQSR, je créé un meeting depuis le studio en invitant `tools@bonjour.io`
- [ ] ETQSR, je vérifie que le meeting est bien visible dans Google Calendar
- [ ] ETQ `tools@bonjour.io`, je vérifie que je reçois un mail d'invitation avec un lien vers le viewer
- [ ] ETQSR, je modifie le meeting depuis le studio
- [ ] ETQSR, je vérifie que le meeting est bien mis à jour dans Google Calendar
- [ ] ETQ `tools@bonjour.io`, je vérifie que je reçois un mail de mise à jour
- [ ] ETQSR, je supprime le meeting depuis le studio
- [ ] ETQSR, je vérifie que le meeting est bien supprimé dans Google Calendar
- [ ] ETQ `tools@bonjour.io`, je vérifie que je reçois un mail d'annulation de l'événement

#### Mise à jour des événements depuis Google Calendar

- [ ] ETQSR, je créé un meeting depuis Google Calendar
  * qui contient @BonjourMeeting (dev) | #BonjourStaging (staging) | #BonjourPreprod (preprod)
  * en invitant `tools@bonjour.io`
  * sans envoyer de notification aux invités
- [ ] ETQSR, je lance l'application et je me Google Login
- [ ] ETQSR, je vérifie que le meeting est bien visible dans le studio
- [ ] ETQ `tools@bonjour.io`, je vérifie que je reçois un mail de mise à jour de l'événement avec un lien vers le viewer
- [ ] ETQSR, je modifie le meeting depuis Google Calendar sans envoyer de notification aux invités
- [ ] ETQSR, je vérifie que le meeting est bien mis à jour dans le studio
- [ ] ETQ `tools@bonjour.io`, je vérifie que je ne reçois pas de mail de mise à jour
- [ ] ETQSR, je supprime le meeting depuis Google Calendar
- [ ] ETQSR, je vérifie que le meeting est bien supprimé dans le studio
- [ ] ETQ `tools@bonjour.io`, je vérifie que je reçois un mail d'annulation de l'événement


## Je fais une non reg sur le meeting note templates

- [ ] ETQSR, je clique sur instant meeting et je vois bien le template picker
- [ ] ETQSR, je clique sur empty note et je me retrouve dans l'edition de note vide
- [ ] ETQSR, je quitte le meeting, je clique sur instant meeting et j'appuis sur le button create note template
- [ ] ETQSR, je créé un note template et il apparait bien dans la liste
- [ ] ETQSR, j'edit le note template (titre et contenu) et je vois bien l'update dans la liste
- [ ] ETQSR, j'appuis sur le nouveau note template, il est bien inséré dans les notes
- [ ] ETQSR, je ferme le meeting, je clique sur instant meeting, je supprime le note template juste créé, il est bien supprimé

## Je fais une non régression sur la sélection des devices

<p style="padding: 5px; background-color: #fff3cd">
💡 Pour faire cette non régression il est recommandé d'avoir plusieurs caméras et plusieurs micros

- utilisez une caméra virtuelle https://snapcamera.snapchat.com/
- utilisez un headset pour avoir plusieurs micros
</p>

<p style="padding: 5px; background-color: #fff3cd">
⚠️ Si pendant les switch de device des glitch/flash/lenteurs visuels apparaissent c'est une regression
</p>

### Studio

<p style="padding: 5px; background-color: #fff3cd">
💡 Pré requis:

- Je vide mon local storage
- Je quitte le studio et le relance
</p>

- [ ] Je créé un instant meeting
  - ma vidéo s'affiche correctement et le bouton est vert
  - le bouton du micro est vert
- [ ] Je désactive la caméra
  - il n'y a plus d'image
  - la lumière verte est stoppée
  - le bouton caméra est rouge + barré
- [ ] Je réactive la caméra
  - le bouton caméra est vert et pas barré
  - l'image revient
- [ ] Je désactive de nouveau la caméra
- [ ] J'ouvre les settings
  - je vois bien mes caméras disponibles et ma caméra par défaut est sélectionnée
  - je vois bien les micros disponibles et le micro par défaut est sélectionné
  - je vois bien les speakers disponibles et le micro par défaut est sélectionné
- [ ] Je change la caméra et j'observe que le feedback camera est désactivé aussi
- [ ] Je change le microphone
- [ ] Je reload le studio et je reviens a la même étape
- [ ] Les devices précédemment sélectionnés sont toujours les mêmes
- [ ] Je ferme les settings
  - la caméra est toujours désactivée
- [ ] Je réactive la caméra
  - je vois l'image de la nouvelle caméra
- [ ] Je désactive le micro
  - le bouton micro est rouge et barré
- [ ] J'ouvre les settings
  - il n'y a pas de feedback visuel du niveau sonore
- [ ] Je change de micro
  - quand je parle le micro devient vert
- [ ] Je ferme les settings
  - le bouton micro est toujours rouge et barré
- [ ] Je réactive le micro
  - le bouton micro est vert
  - la tooltip montre le nom du nouveau micro sélectionné
- [ ] Je déconnecte mon headset
  - je vois que mon micro a changé pour le micro par défaut et il n'est pas muted
- [ ] Je connecte mon headset
  - je vois que mon micro a changé pour le micro du headset connecté et il est muted
- [ ] J'unmute et le bouton micro passe au vert
- [ ] Je démarre le call
  - la caméra est bien celle que j'ai sélectionné
  - les boutons camera et micro sont verts
- [ ] Je stop le call
  - je vois l'image de ma caméra
- [ ] Je retourne à la home
  - la lumiere verte est stopée

### Viewer
<p style="padding: 5px; background-color: #fff3cd">
💡 Pré requis:

- Être sur safari
- Je vide mon local storage
</p>

- [ ] je le rejoins un preshow avec le viewer SANS accorder les permissions camera ni micro
  - Je vois des `!` a coté des boutons media
- [ ] je reload la page et accorde les permissions
  - ma vidéo s'affiche correctement et le bouton est vert
  - le bouton du micro est vert
- [ ] Je désactive la caméra
  - il n'y a plus d'image
  - la lumière verte est stoppée (⚠️ vérifier qu'aucun autre onglet ou app n'utilise la caméra si elle est toujours allumée)
  - le bouton caméra est rouge + barré
- [ ] Je réactive la caméra
  - le bouton caméra est vert et pas barré
  - l'image revient
- [ ] Je désactive de nouveau la caméra
- [ ] J'ouvre les settings
  - je vois bien mes caméras disponibles et ma caméra par défaut est sélectionnée
  - je vois bien les micros disponibles et le micro par défaut est sélectionné
  - je vois bien les speakers disponibles et le micro par défaut est sélectionné
- [ ] Je change la caméra et j'observe que le feedback camera est désactivé aussi
- [ ] Je change le microphone
- [ ] Je reload le viewer et je reviens a la même étape
- [ ] Les devices précédemment sélectionnés sont toujours les mêmes
- [ ] Je ferme les settings
  - la caméra est toujours désactivée
- [ ] Je réactive la caméra
  - je vois l'image de la nouvelle caméra
- [ ] Je désactive le micro
  - le bouton micro est rouge et barré
- [ ] J'ouvre les settings
  - quand je parle j'observe qu'il n'y a pas de feedback visuel
- [ ] Je change de micro
  - quand je parle le micro devient vert
- [ ] Je ferme les settings
  - le bouton micro est toujours rouge et barré
- [ ] Je réactive le micro
  - le bouton micro est vert
  - la tooltip montre le nom du nouveau micro sélectionné
- [ ] Je démarre le call
  - la caméra est bien celle que j'ai sélectionné
  - les boutons camera et micro sont verts
- [ ] Je déconnecte mon headset
  - je vois que mon micro a changé pour le micro par défaut et il n'est pas muted
- [ ] Je connecte mon headset
  - je vois que mon micro a changé pour le micro du headset connecté et il n'est pas muted
- [ ] J'ouvre les settings et je change de caméra
  - l'image vient bien de la caméra que j'ai sélectionné

### Je fais une non régression Manager

#### Call

- [ ] J'ai bien été redirigé vers le bon call après avoir clické sur le recording dans l'onglet recording du studio

#### Comments

- [ ] Je créé un comment a un moment !== 0 dans la vidéo
- [ ] Le comment apparait au bon endroit
- [ ] Je reply au comment
- [ ] Je fais un second reply
- [ ] J'edit le second reply et je mentionne quelqu'un
- [ ] Je delete le second reply
- [ ] Je delete le premier message qui est le parent du thread
- [ ] Je vois "🗑 This message was deleted. Deleted a few seconds ago"
- [ ] Je supprime le dernier message du thread et le parent disparait

#### Transcript

- [ ] Au chargement de la page je vois "getting transcript"
- [ ] Le transcript entier apparait après le chargement
- [ ] Si je change de locale je vois "Transcript in progress..."
- [ ] Le transcript dans le nouvelle locale apparait
- [ ] Si je cherche un mot dans la search bar la recherche s'effectue
