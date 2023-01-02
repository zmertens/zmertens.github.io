import { Component, OnInit } from '@angular/core';
import { RepoService } from '../repo.service';
import { Repo } from '../repo'

@Component({
  selector: 'app-repo-list',
  templateUrl: './repo-list.component.html',
  styleUrls: ['./repo-list.component.css']
})
export class RepoListComponent implements OnInit {
  repoes: Repo[] = [];

  constructor(private repoService: RepoService) { }

  ngOnInit(): void {
    this.repoService.getRepoes().subscribe(repoes => this.repoes = repoes);
  }

}
