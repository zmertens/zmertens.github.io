import { Component, OnInit } from '@angular/core';
import { NgForm } from '@angular/forms/forms';
import { RepoService } from '../repo.service';

@Component({
  selector: 'app-repo-detail',
  templateUrl: './repo-detail.component.html',
  styleUrls: ['./repo-detail.component.css']
})
export class RepoDetailComponent implements OnInit {

  constructor(private repoService: RepoService) { }

  ngOnInit(): void {
  }

  submit(f: NgForm): void {
    if (f.valid) {
      let name = f.controls['input1'].value;
      let desc = f.controls['input2'].value;
      // console.log(`repo name: ${name}, repo desc: ${desc}`);
      // Assume repo id's are sequential
      let repoLastId;
      this.repoService.getRepoes().subscribe(repoes => {
        repoLastId = repoes[repoes.length - 1].id++;
      });

      this.repoService.addRepo({id: repoLastId, name: name, description: desc});

      f.resetForm();
    }
  }
}
