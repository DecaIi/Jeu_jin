class PlayerLeftcomand: public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionLef();
	}
private:

};
